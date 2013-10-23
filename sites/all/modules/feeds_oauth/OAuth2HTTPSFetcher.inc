<?php

/**
 * Definition of the import batch object created on the fetching stage by
 * OAuth2HTTPSFetcher.
 */
class OAuth2HTTPSFetcherResult extends FeedsFetcherResult {
  protected $url;
  protected $authenticator;
  protected $consumer_key;
  protected $consumer_secret;
  protected $id;
  protected $site_id;
  protected $uid;

  /**
   * Constructor.
   */
  public function __construct($url, $authenticator, $consumer_key, $consumer_secret, $id, $site_id, $uid) {
    $this->url = $url;
    $this->authenticator = $authenticator;
    $this->consumer_key = $consumer_key;
    $this->consumer_secret = $consumer_secret;
    $this->id = $id;
    $this->site_id = $site_id;
    $this->uid = $uid;
    parent::__construct('');
  }

  /**
   * Implementation of FeedsFetcherBatch::getRaw().
   */
  public function getRaw() {
    $path = variable_get('feeds_oauth_library_path', FEEDS_OAUTH_LIBRARY_PATH_DEFAULT);
    require_once($path . '/lib/oauth/OAuth2Client.php');
    $access_token = call_user_func($this->authenticator, $this->uid, $this->site_id, $this->id);
    $oauth = new OAuth2CurlClient();
    $oauth->_setAccessToken(new OAuth2AccessToken($access_token['oauth_token']));
    $request = $oauth->createGetRequest($this->url, array('access_token' => $oauth->getAccessToken()->getToken()));
    $response = $oauth->executeRequest($request);
    if ($response->getStatusCode() == 200) {
      return $response->getBody();
    }
    else {
      watchdog('feeds_oauth', print_r($response->getBody(), TRUE), array());
    }
  }
}

/**
 * Support OAuth 2.0 authentication.
 */
class OAuth2HTTPSFetcher extends FeedsHTTPFetcher {
  /**
   * Use signed URL to fetch content.
   */
  public function fetch(FeedsSource $source) {
    $source_config = $source->getConfigFor($this);
    $source_node = node_load($source->feed_nid);
    global $user;
    return new OAuth2HTTPSFetcherResult(
      trim($source_config['source']),
      $this->config['authenticator'],
      $this->config['consumer_key'],
      $this->config['consumer_secret'],
      $this->id,
      $this->config['site_id'],
      $source_node ? $source_node->uid : $user->uid
    );
  }

  /**
   * Declare defaults.
   */
  public function configDefaults() {
    return array(
      'authenticator' => 'feeds_oauth_get_tokens',
      'site_id' => '',
      'consumer_key' => '',
      'consumer_secret' => '',
      'access_token_url' => '',
      'authorize_url' => '',
      'scope' => '',
    ) + parent::configDefaults();
  }

  /**
   * Add form options.
   */
  public function configForm(&$form_state) {
    $form = parent::configForm($form_state);
    $form['use_pubsubhubbub'] = array('#type' => 'value', '#value' => FALSE);
    $form['authenticator'] = array(
      '#type' => 'select',
      '#title' => t('OAuth authenticator'),
      '#default_value' => $this->config['authenticator'],
      '#options' => module_invoke_all('feeds_oauth_authenticator'),
      '#description' => t('Choose the authentication module that provides the needed OAuth tokens.'),
    );
    $form['site_id'] = array(
      '#type' => 'textfield',
      '#title' => t('Site identifier'),
      '#default_value' => $this->config['site_id'],
      '#description' => t('Internal identifier for this connection. Should only contain alphanumeric characters and hyphens. For the current configuration, callback URL will be: <code class="site-id">%url</code>',
        array('%url' => url('feeds/oauth2/callback/' . $this->config['site_id'], array('absolute' => TRUE)))
      ),
      '#required' => TRUE,
      '#attached' => array(
        'js' => array(
          drupal_get_path('module', 'feeds_oauth') . '/feeds_oauth.js',
        ),
      ),
    );
    $form['consumer_key'] = array(
      '#type' => 'textfield',
      '#title' => t('Consumer key'),
      '#default_value' => $this->config['consumer_key'],
      '#required' => TRUE,
    );
    $form['consumer_secret'] = array(
      '#type' => 'textfield',
      '#title' => t('Consumer secret'),
      '#default_value' => $this->config['consumer_secret'],
      '#required' => TRUE,
    );
    $form['access_token_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Access token URL'),
      '#default_value' => $this->config['access_token_url'],
      '#required' => TRUE,
    );
    $form['authorize_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Authorize URL'),
      '#default_value' => $this->config['authorize_url'],
      '#required' => TRUE,
    );
    $form['scope'] = array(
      '#type' => 'textarea',
      '#title' => t('Scope'),
      '#description' => t('Scope of the authorization request, one per line or comma-separated.'),
      '#default_value' => $this->config['scope'],
    );
    return $form;
  }

  /**
   * Validate config.
   */
  public function configFormValidate(&$values) {
    $values['site_id'] = trim($values['site_id']);
    if (!preg_match('/^[\w-]*$/', $values['site_id'])) {
      form_set_error('site_id', t('Site identifier must be alphanumerics and hyphens only.'));
    }
  }

  /**
   * Expose source form.
   */
  public function sourceForm($source_config) {
    $form = parent::sourceForm($source_config);
    global $user;
    $access_tokens = call_user_func($this->config['authenticator'], $user->uid, $this->config['site_id'], $this->id);
    if (empty($access_tokens) && !empty($this->config['site_id'])) {
      drupal_set_message(t('Could not find OAuth access tokens for site %site. You should probably <a href="@url">authenticate first</a> to access protected information.',
          array('%site' => $this->config['site_id'], '@url' => url('feeds/oauth2/authenticate/' . $this->id))
      ), 'warning', FALSE);
    }
    return $form;
  }
}


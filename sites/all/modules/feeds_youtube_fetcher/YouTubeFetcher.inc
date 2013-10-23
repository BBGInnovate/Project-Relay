<?php
/**
 * Result of FeedsHTTPFetcher::fetch().
 */
class YouTubeFetcherResult extends FeedsHTTPFetcherResult {
  protected $state = null;

  /**
   * Constructor.
   */
  public function __construct($url = NULL, FeedsSource $source = null) {
    $this->state = $source->state(FEEDS_FETCH);
    $url = !empty($this->state->next_url) ? $this->state->next_url : $url;
    parent::__construct($url);
  }

  /**
   * Overrides FeedsHTTPFetcherResult::getRaw();
   */
  public function getRaw() {
    $xml = parent::getRaw();

    // Get the playlist element.
    $playlist = new SimpleXMLElement($xml);
    $counts = $playlist->children('http://a9.com/-/spec/opensearch/1.1/');
    $total = intval($counts->totalResults);
    $size = intval($counts->itemsPerPage);
    $start = intval($counts->startIndex);

    // Calculate the new state based on this feeds data.
    $this->state->total = ceil($total / $size);
    $this->state->count = ceil($start / $size);
    $next = $start + $size;
    if (strpos($this->url, 'start-index') !== FALSE) {
      $this->state->next_url = str_replace('start-index=' . $start, 'start-index=' . $next, $this->url);
    }
    else {
      $this->state->next_url = $this->url . '&start-index=' . $next;
    }
    $this->state->progress($this->state->total, $this->state->count);

    // Return the XML.
    return $xml;
  }
}

/**
 * Fetches data via HTTP.
 */
class YouTubeFetcher extends FeedsHTTPFetcher {

  /**
   * Implements FeedsFetcher::fetch().
   */
  public function fetch(FeedsSource $source) {
    $source_config = $source->getConfigFor($this);
    return new YouTubeFetcherResult($source_config['source'], $source);
  }
}

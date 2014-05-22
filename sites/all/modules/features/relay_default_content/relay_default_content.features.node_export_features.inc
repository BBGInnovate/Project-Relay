<?php
/**
 * @file
 * relay_default_content.features.node_export_features.inc
 */

/**
 * Implements hook_node_export_features_default().
 */
function relay_default_content_node_export_features_default() {
  $node_export = array(
  'code_string' => 'array(
  (object) array(
      \'vid\' => \'1\',
      \'uid\' => \'1\',
      \'title\' => \'Default Video Content\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'1\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'b6c8ac06-ff99-44fe-95b1-1233a67a8182\',
      \'nid\' => \'1\',
      \'type\' => \'relay_video\',
      \'language\' => \'und\',
      \'created\' => \'1400706969\',
      \'changed\' => \'1400706969\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'b99dfac4-7d86-4490-883d-7961766f9996\',
      \'revision_timestamp\' => \'1400706969\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'<iframe width="853" height="480" src="//www.youtube.com/embed/7A5qfbjsnJA?rel=0" frameborder="0" allowfullscreen></iframe>\',
            \'summary\' => \'\',
            \'format\' => \'filtered_html\',
            \'safe_value\' => \'\',
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'relay_pin_card\' => array(
        \'und\' => array(
          array(
            \'value\' => \'0\',
          ),
        ),
      ),
      \'relay_authors\' => array(
        \'und\' => array(
          array(
            \'value\' => \'Jason Michael Perry\',
            \'format\' => NULL,
            \'safe_value\' => \'Jason Michael Perry\',
          ),
        ),
      ),
      \'relay_events_ref\' => array(
        \'und\' => array(
          array(
            \'tid\' => \'1\',
          ),
        ),
      ),
      \'relay_addthis\' => array(
        \'und\' => array(
          array(
            \'value\' => \'Dummy value\',
          ),
        ),
      ),
      \'relay_tweet_status_id\' => array(),
      \'relay_video_file\' => array(),
      \'relay_youtube_code\' => array(
        \'und\' => array(
          array(
            \'value\' => \'7A5qfbjsnJA\',
            \'format\' => NULL,
            \'safe_value\' => \'7A5qfbjsnJA\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1400706969\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'name\' => \'dcward\',
      \'picture\' => \'0\',
      \'data\' => \'b:0;\',
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'2\',
      \'uid\' => \'1\',
      \'title\' => \'Default Relay Article\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'1\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'8d8cb7aa-8808-4384-a0ec-1ee32fab5e74\',
      \'nid\' => \'2\',
      \'type\' => \'relay_article\',
      \'language\' => \'und\',
      \'created\' => \'1400707018\',
      \'changed\' => \'1400707018\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'d2649e44-dbca-4daf-97ff-188db3dac2a3\',
      \'revision_timestamp\' => \'1400707018\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'Parturient eu tincidunt purus arcu integer et. Augue a, augue augue platea sociis sagittis ac? Phasellus integer auctor elit turpis placerat aliquam mattis cras etiam ridiculus, ridiculus quis odio, magnis odio cras integer magna odio, pellentesque tempor cras turpis et sagittis.\',
            \'summary\' => \'\',
            \'format\' => \'filtered_html\',
            \'safe_value\' => "<p>Parturient eu tincidunt purus arcu integer et. Augue a, augue augue platea sociis sagittis ac? Phasellus integer auctor elit turpis placerat aliquam mattis cras etiam ridiculus, ridiculus quis odio, magnis odio cras integer magna odio, pellentesque tempor cras turpis et sagittis.</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'relay_pin_card\' => array(
        \'und\' => array(
          array(
            \'value\' => \'0\',
          ),
        ),
      ),
      \'relay_authors\' => array(
        \'und\' => array(
          array(
            \'value\' => \'Jason Michael Perry\',
            \'format\' => NULL,
            \'safe_value\' => \'Jason Michael Perry\',
          ),
        ),
      ),
      \'relay_events_ref\' => array(
        \'und\' => array(
          array(
            \'tid\' => \'1\',
          ),
        ),
      ),
      \'relay_addthis\' => array(
        \'und\' => array(
          array(
            \'value\' => \'Dummy value\',
          ),
        ),
      ),
      \'relay_tweet_status_id\' => array(),
      \'relay_more_link\' => array(),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1400707018\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'name\' => \'dcward\',
      \'picture\' => \'0\',
      \'data\' => \'b:0;\',
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
)',
);
  return $node_export;
}

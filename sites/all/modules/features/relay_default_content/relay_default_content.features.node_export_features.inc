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
      \'title\' => \'About Relay\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'6529043e-cbc4-45e0-9f0c-3302da22a52f\',
      \'nid\' => \'1\',
      \'type\' => \'page\',
      \'language\' => \'und\',
      \'created\' => \'1401765270\',
      \'changed\' => \'1401765270\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'a2f43b56-1b04-414a-9a4e-d9302b0da70b\',
      \'revision_timestamp\' => \'1401765270\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'Here is the text.\',
            \'summary\' => \'\',
            \'format\' => \'full_html\',
            \'safe_value\' => "<p>Here is the text.</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
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
      \'last_comment_timestamp\' => \'1401765270\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'name\' => \'dcward\',
      \'picture\' => \'0\',
      \'data\' => \'b:0;\',
      \'menu\' => NULL,
      \'path\' => FALSE,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'2\',
      \'uid\' => \'1\',
      \'title\' => \'Default Video Content\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'1\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'b6c8ac06-ff99-44fe-95b1-1233a67a8182\',
      \'nid\' => \'2\',
      \'type\' => \'relay_video\',
      \'language\' => \'und\',
      \'created\' => \'1401765270\',
      \'changed\' => \'1401765270\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'b99dfac4-7d86-4490-883d-7961766f9996\',
      \'revision_timestamp\' => \'1401765270\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'<iframe width="853" height="480" src="//www.youtube.com/embed/6v2L2UGZJAM?rel=0" frameborder="0" allowfullscreen></iframe>\',
            \'summary\' => \'\',
            \'format\' => \'full_html\',
            \'safe_value\' => \'<iframe width="853" height="480" src="//www.youtube.com/embed/6v2L2UGZJAM?rel=0" frameborder="0" allowfullscreen=""></iframe>\',
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'relay_pin_card\' => array(
        \'und\' => array(
          array(
            \'value\' => \'1\',
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
            \'tid\' => \'2\',
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
            \'value\' => \'6v2L2UGZJAM\',
            \'format\' => NULL,
            \'safe_value\' => \'6v2L2UGZJAM\',
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
      \'last_comment_timestamp\' => \'1401765270\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'name\' => \'dcward\',
      \'picture\' => \'0\',
      \'data\' => \'b:0;\',
      \'menu\' => NULL,
      \'path\' => FALSE,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'3\',
      \'uid\' => \'1\',
      \'title\' => \'Contact Us\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'9440b7c9-c616-4fa5-856b-90dc9c5bf772\',
      \'nid\' => \'3\',
      \'type\' => \'page\',
      \'language\' => \'und\',
      \'created\' => \'1401765270\',
      \'changed\' => \'1401765270\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'c8097116-25c4-4e46-86f9-e56285ceb136\',
      \'revision_timestamp\' => \'1401765270\',
      \'revision_uid\' => \'1\',
      \'body\' => array(),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
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
      \'last_comment_timestamp\' => \'1401765270\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'name\' => \'dcward\',
      \'picture\' => \'0\',
      \'data\' => \'b:0;\',
      \'menu\' => NULL,
      \'path\' => FALSE,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'4\',
      \'uid\' => \'1\',
      \'title\' => \'Default Relay Article\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'1\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'8d8cb7aa-8808-4384-a0ec-1ee32fab5e74\',
      \'nid\' => \'4\',
      \'type\' => \'relay_article\',
      \'language\' => \'und\',
      \'created\' => \'1401765270\',
      \'changed\' => \'1401765270\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'d2649e44-dbca-4daf-97ff-188db3dac2a3\',
      \'revision_timestamp\' => \'1401765270\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'Parturient eu tincidunt purus arcu integer et. Augue a, augue augue platea sociis sagittis ac? Phasellus integer auctor elit turpis placerat aliquam mattis cras etiam ridiculus, ridiculus quis odio, magnis odio cras integer magna odio, pellentesque tempor cras turpis et sagittis.\',
            \'summary\' => \'\',
            \'format\' => \'full_html\',
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
      \'last_comment_timestamp\' => \'1401765270\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'name\' => \'dcward\',
      \'picture\' => \'0\',
      \'data\' => \'b:0;\',
      \'menu\' => NULL,
      \'path\' => FALSE,
      \'node_export_drupal_version\' => \'7\',
    ),
)',
);
  return $node_export;
}

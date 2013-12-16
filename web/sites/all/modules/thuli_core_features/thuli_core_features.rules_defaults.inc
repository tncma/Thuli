<?php
/**
 * @file
 * thuli_core_features.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function thuli_core_features_default_rules_configuration() {
  $items = array();
  $items['rules_thuli_on_approved'] = entity_import('rules_config', '{ "rules_thuli_on_approved" : {
      "LABEL" : "When a Thuli gets approved",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "userpoints_rules", "gcm" ],
      "ON" : { "node_update--thuli" : { "bundle" : "thuli" } },
      "IF" : [
        { "data_is" : { "data" : [ "node-unchanged:field-state" ], "value" : "1" } },
        { "AND" : [] },
        { "data_is" : { "data" : [ "node:field-state" ], "value" : "2" } }
      ],
      "DO" : [
        { "userpoints_action_grant_points" : {
            "user" : [ "node:author" ],
            "points" : "25",
            "tid" : "0",
            "entity" : [ "" ],
            "operation" : "Insert",
            "display" : 1,
            "moderate" : "approved"
          }
        },
        { "gcm_action_send_message" : {
            "tokens" : "[node:author]",
            "keyValue" : "body=Congratulations, your Thuli has been accepted!",
            "delay_while_idle" : 1
          }
        }
      ]
    }
  }');
  return $items;
}

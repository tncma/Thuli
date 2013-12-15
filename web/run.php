<?php

// Ensure anonymity
$anonymous = user_is_anonymous();
if ($anonymous) {
  echo "User is anonymous.\n";
}
$stub = (object) array(
  'type' => 'thuli'
);
$access = node_access('create', 'thuli');
var_dump($access);
<?php
/**
 * trms_production_update_action.inc
 *
 * @package default
 */


/**
 *
 *
 * @param unknown $node    (reference)
 * @param unknown $context (optional)
 */
function trms_production_update_action(&$node, $context = array()) {

	node_save($node);

	$show_date_str = substr($node->field_production_date[0]['value'], 0, 10);
	$hours = substr($node->field_duration[0]['value'], 0, 2);
	$minutes = substr($node->field_duration[0]['value'], 3, 2);
	$seconds = substr($node->field_duration[0]['value'], 5, 2);
	$length = ($hours * 3600) + ($minutes * 60) + $seconds;

	$url = variable_get('trms_url','http://localhost');
	$username = variable_get('trms_username','admin');
	$password = variable_get('trms_password','password');
	$channel = variable_get('trms_channel','1');

}

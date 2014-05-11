<?php
/**
 * trms_production_add_action.inc
 *
 * @package default
 */


/**
 *
 *
 * @param unknown $node  (reference)
 * @param unknown $context (optional)
 */
function trms_production_add_action(&$node, $context = array()) {

//   print "<pre>";
//   print_r($node);
//   print "</pre>";
//   exit;


	$show_date_str = substr($node->field_production_date[0]['value'], 0, 10);
	$hours = substr($node->field_duration[0]['value'], 0, 2);
	$minutes = substr($node->field_duration[0]['value'], 3, 2);
	$seconds = substr($node->field_duration[0]['value'], 5, 2);
	$length = ($hours * 3600) + ($minutes * 60) + $seconds;

        $url = variable_get('trms_url','http://localhost');
        $username = variable_get('trms_username','admin');
        $password = variable_get('trms_password','password');
        $channel = variable_get('trms_channel','1');

	try {
		$client = new SoapClient($url . "/CablecastWS.asmx?WSDL");
		$params = array(
			'LocalID' => $node->nid,
			'LocationID' => 22,
			'Title' => $node->title,
			'CGTitle' => $node->title,
			'ProjectID' => 0,
			'CGExempt' => false,
			'ProducerID' => $node->producer,
			'ChannelID' => $channel,
			'FormatID' => 70,
			'Reels' => array(
				'NewReel' => array('FormatID' => 70,
					'CueSeconds' => 0,
					'LengthSeconds' => $length,
					'Title' => 0,
					'Chapter' => 0
				)
			),
			'CategoryID' => $node->category,
			'EventDate' => $show_date_str,
			'Comments' => '',
			'CustomFields' => array(
				'CustomField' => array()
			),
			'OnDemand' => false,
			'OnDemandStatus' => '',
			'BugText' => '',
			'CrawlText' => '',
			'CrawlLengthInSeconds' => 0,
			'username' => $username,
			'password' => $password
		);

		$result = $client->CreateNewShowRecord($params);
                $show_id = $result->CreateNewShowRecordResult;
		$node->field_show_id[0]['value'] = $show_id;
		node_save($node);
	} catch (SOAPFault $exception) {
                form_set_error('title', $exception->getMessage());
	}


}





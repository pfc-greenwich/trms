<?php
/**
 * trms_select_fields.inc
 *
 * @package default
 */


/**
 *
 *
 * @return unknown
 */
function trms_producers() {

        $url = variable_get('trms_url');
        $channel = variable_get('trms_channel');

	$items = array();
        ini_set('default_socket_timeout', 1);
	try {
		$client = new SoapClient($url . "/CablecastWS.asmx?WSDL",array("connection_timeout"=>3));
		$params = array('ChannelID' => $channel);
		$result = $client->GetProducers($params);
	} catch (SOAPFault $exception) {
		return $items;
	}


	foreach ($result->GetProducersResult->Producer as $item) {
		$items[$item->ProducerID] = $item->Name;
	}
	return $items;
}


/**
 *
 *
 * @return unknown
 */
function trms_categories() {

        $url = variable_get('trms_url');
        $channel = variable_get('trms_channel');

	$items = array();
	ini_set('default_socket_timeout', 1);
	try {
		$client = new SoapClient($url . "/CablecastWS.asmx?WSDL",array("connection_timeout"=>3));
		$params = array('ChannelID' => $channel);
		$result = $client->GetCategories($params);
	} catch (SOAPFault $exception) {
		return $items;
	}


	foreach ($result->GetCategoriesResult->Category as $item) {
		$items[$item->CategoryID] = $item->Name;
	}
	return $items;
}

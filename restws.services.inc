<?php
// $Id$

/**
 * @file
 * Export of RESTful web services' Services endpoint
 */

/**
 * Implementation of hook_default_services_endpoint().
 */
function restws_default_services_endpoint() {
  $endpoints = array();
  $base = array(
    'operations' => array(
      'retrieve' => array(
        'enabled' => 1,
      ),
      'create' => array(
        'enabled' => 1,
      ),
      'update' => array(
        'enabled' => 1,
      ),
      'delete' => array(
        'enabled' => 1,
      ),
    ),
  );

  $endpoint = new stdClass;
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->api_version = 3;
  $endpoint->name = 'restws';
  $endpoint->title = 'RESTful web services';
  $endpoint->server = 'rest_server';
  $endpoint->path = 'restws';
  $endpoint->authentication = array();
  $endpoint->resources = array(
    'restws_node' => array(
      'alias' => 'node',
    ),
    'restws_comment' => array(
      'alias' => 'comment',
      'operations' => array(
        'create' => array(
          'enabled' => 1,
        ),
        'retrieve' => array(
          'enabled' => 1,
        ),
        'update' => array(
          'enabled' => 1,
        ),
        'delete' => array(
          'enabled' => 1,
        ),
      ),
    ),
  );
  $endpoint->debug = 1;
  $endpoint->status = 1;

  foreach (entity_get_info() as $entity_type => $info) {
    $endpoint->resources['restws_' . $entity_type] = array('alias' => $entity_type) + $base;
  }

  $endpoints[$endpoint->name] = $endpoint;

  return $endpoints;
}

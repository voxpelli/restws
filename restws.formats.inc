<?php
// $Id$

/**
 * @file
 * RESTful web services module formats.
 */

/**
 * Interface implemented by formatter implementations for the http client.
 */
interface RestWSFormatInterface {

  /**
   * Gets the representation of a resource.
   *
   * @param RestWSResourceControllerInterface $resourceController
   *   The controller used to retrieve the resource.
   * @param $id
   *   The id of the resource that should be returned.
   *
   * @return
   *   The representation of the resource.
   */
  public function viewResource($resourceController, $id);

  /**
   * Create a resource.
   *
   * @param RestWSResourceControllerInterface $resourceController
   *   The controller used to create the resource.
   * @param $data
   *   The representation of the resource.
   *
   * @return
   *   The id of the newly created resource.
   */
  public function createResource($resourceController, $data);

  /**
   * Update a resource.
   *
   * @param RestWSResourceControllerInterface $resourceController
   *   The controller used to update the resource.
   * @param $id
   *   The id of the resource that should be updated.
   * @param $data
   *   The representation of the resource.
   */
  public function updateResource($resourceController, $id, $data);

  /**
   * Delete a resource.
   *
   * @param RestWSResourceControllerInterface $resourceController
   *   The controller used to update the resource.
   * @param $id
   *   The id of the resource that should be deleted.
   */
  public function deleteResource($resourceController, $id);


  /**
   * Returns the mime type of this format, e.g. 'application/json' or
   * 'application/xml'.
   */
  public function mimeType();
}

/**
 * A base for all simple formats that are just serializing/unserializing values.
 */
abstract class RestWSBaseFormat implements RestWSFormatInterface {

  protected $formatName;
  protected $formatInfo;

  public function __construct($name, $info) {
    $this->formatName = $name;
    $this->formatInfo = $info;
  }

  /**
   * Gets the representation of a resource.
   */
  public function viewResource($resourceController, $id) {
    $values = $resourceController->read($id);
    return $this->serialize($values);
  }

  /**
   * Creates a new resource.
   */
  public function createResource($resourceController, $data) {
    $values = $this->unserialize($data);
    $uri = $resourceController->create($values);
    return $this->serialize($uri);
  }

  /**
   * Updates a resource.
   */
  public function updateResource($resourceController, $id, $data) {
    $values = $this->unserialize($data);
    $resourceController->update($id, $values);
  }

  /**
   * Deletes a resource.
   */
  public function deleteResource($resourceController, $id) {
    $resourceController->delete($id);
  }

  public function mimeType() {
    return $this->formatInfo['mime type'];
  }
}

/**
 * A formatter to format json.
 */
class RestWSFormatJSON extends RestWSBaseFormat {

  public function serialize(array $values) {
    return drupal_json_encode($values);
  }

  public function unserialize($data) {
    return drupal_json_decode($data);
  }
}

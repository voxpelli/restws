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
   * Serializes arbitrary data values.
   *
   * @param array $values
   *  The data that should be serialized.
   *
   * @return
   *  The serialized data as a string.
   */
  public function serialize(array $values);

  /**
   * Unserializes data.
   *
   * @param string $data
   *  The data that should be unserialized.
   *
   * @return
   *  The unserialized data.
   */
  public function unserialize($data);
}

/**
 * A base for all simple formats that are just serializing/unserializing values.
 */
abstract class RestWSBaseFormat implements RestWSFormatInterface {

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
    return $resourceController->create($values);
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
}

/**
 * A base formatter to format json.
 */
class RestWSFormatJSON extends RestWSBaseFormat {

  /**
   * Creates a new resource.
   */
  public function createResource($resourceController, $data) {
    $values = $this->unserialize($data);
    return drupal_json_encode($resourceController->create($values));
  }

  public function serialize(array $values) {
    return drupal_json_encode($values);
  }

  public function unserialize($data) {
    return drupal_json_decode($data);
  }
}

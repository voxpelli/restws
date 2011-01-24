<?php
// $Id$

/**
 * @file
 * RESTful web services module integration for entities.
 */

/**
 * Specifies CRUD and access methods for resources.
 */
interface RestWSResourceControllerInterface {

  /**
   * Create a new resource.
   *
   * @param array $values
   *   Array that represents the resource.
   */
  public function create(array $values);

  /**
   * Returns an existing resource.
   *
   * @param $id
   *   The id of the resource that should be returned.
   *
   * @return
   *   An array representing the resource.
   */
  public function read($id);

  /**
   * Update an existing resource.
   * @param $id
   *   The id of the resource that should be updated.
   * @param array $values
   *   Array that represents the resource.
   */
  public function update($id, array $values);

  /**
   * Delete an existing resource.
   *
   * @param $id
   *   The id of the resource that should be deleted.
   */
  public function delete($id);

  /**
   * Determines access for a given operation and resource.
   *
   * @param $operation
   *   Either 'create', 'view' (= read), 'update' or 'delete'.
   * @param $id
   *   The id of the resource.
   *
   * @see entity_access()
   */
  public function access($operation, $id);
}

/**
 * Controller for entity-bases resources.
 */
class RestWSEntityResourceController implements RestWSResourceControllerInterface {

  protected $entityType, $entityInfo;

  public function __construct($name, $info) {
    $this->entityType = $name;
    $this->entityInfo = entity_get_info($name);
  }

  /**
   * Returns the property info for the given resource.
   */
  public function propertyInfo() {
    return entity_get_property_info($this->entityType);
  }

  /**
   * Returns a metadata wrapper for the resource with the given id.
   */
  public function wrapper($id) {
    return entity_metadata_wrapper($this->entityType, $id);
  }

  /**
   * Returns a metadata wrapper for the resource with the given id.
   */
  public function read($id) {
    return entity_metadata_wrapper($this->entityType, $id);
  }

  /**
   * Creates a new resource with values matching the property info.
   */
  public function create(array $values) {
    return entity_property_values_create_entity($this->entityType, $values);
  }

  /**
   * Updates a resource with values matching the property info.
   */
  public function update($id, $values) {
    $wrapper = $this->wrapper($id);
    foreach ($values as $name => $value) {
      $wrapper->name->set($value);
    }
    $wrapper->save();
  }

  /**
   * Deletes a resource with the given id.
   */
  public function delete($id) {
    entity_delete($this->entityType, $id);
  }

  /**
   * Determines access for a given resource.
   *
   * @see entity_access()
   */
  public function access($op, $id = NULL) {
    return entity_access($op, $this->entityType, isset($id) ? $this->wrapper($id)->value() : NULL);
  }
}

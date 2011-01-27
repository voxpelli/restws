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
   *
   * @return
   *   An array describing the URI of the newly created resource.
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
   *
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
   * @param $op
   *   Either 'create', 'view' (= read), 'update' or 'delete'.
   * @param $id
   *   The id of the resource.
   *
   * @see entity_access()
   */
  public function access($op, $id);
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
   * Returns an array representing the resource.
   */
  public function read($id) {
    return self::getData($this->wrapper($id));
  }

  /**
   * Creates a new resource with values matching the property info.
   */
  public function create(array $values) {
    $entity = entity_property_values_create_entity($this->entityType, $values);
    $entity->save();
    $id = $entity->getIdentifier();
    return restws_resource_reference($this->entityType, $id);
  }

  /**
   * Updates a resource with values matching the property info.
   */
  public function update($id, array $values) {
    $wrapper = $this->wrapper($id);
    foreach ($values as $name => $value) {
      $wrapper->{$name}->set($value);
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
  public function access($op, $id) {
    return entity_access($op, $this->entityType, isset($id) ? $this->wrapper($id)->value() : NULL);
  }

  /**
   * Gets a simple PHP array using URI references for some wrapped data.
   */
  public static function getData($wrapper) {
    $data = array();
    foreach ($wrapper as $name => $property) {
      try {
        if ($property instanceof EntityDrupalWrapper) {
          // For referenced entities only return the URI.
          if ($id = $property->getIdentifier()) {
            $data[$name] = restws_resource_reference($property->type(), $id);
          }
        }
        elseif ($property instanceof EntityValueWrapper) {
          $data[$name] = $property->value();
        }
        elseif ($property instanceof EntityListWrapper || $property instanceof EntityStructureWrapper) {
          $data[$name] = self::getData($property);
        }
      }
      catch (EntityMetadataWrapperException $e) {
        // A property causes problems - ignore that.
      }
    }
    return $data;
  }
}

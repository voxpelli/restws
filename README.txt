RESTful Web Services for Drupal
===============================

Design goals
============
* Create a module that exposes Drupal resources (e.g. entities) as web
  services. It should be fully compliant to the REST principles.
* The module is strictly resource-oriented. No support for message-oriented or
  RPC-style web services.
* Plain and simple. No need for endpoint configuration, all resources are
  available on the same path pattern. Access via HTTP only.
* When the module is enabled all entities should be available at the URL path
  /<entity type name>/<entity id>, e.g. /node/123, /user/1 or /profile/789.
* CRUD (Create, Read, Update, Delete) support for entities
* Create: HTTP PUT    /<entity type name>.<format>
* Read:   HTTP GET    /<entity type name>/<entity id>.<format>
* Update: HTTP POST   /<entity type name>/<entity id>.<format>
* Delete: HTTP DELETE /<entity type name>/<entity id>
* <format> can be json, xml etc.

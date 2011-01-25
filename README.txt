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
* Resources are represented and exchanged in different formats, e.g. JSON or
  XML. The format has to be specified in every request.
* CRUD (Create, Read, Update, Delete) support for entities
* Create: HTTP PUT /<entity type name> (requires HTTP Accept header set to the
  MIME type of <format>)
* Read: HTTP GET /<entity type name>/<entity id>.<format>
  or    HTTP GET /<entity type name>/<entity id> (requires HTTP Accept header
  set to the MIME type of <format>)
* Update: HTTP POST /<entity type name>/<entity id>.<format>
  or      HTTP POST /<entity type name>/<entity id> (requires HTTP Accept header
  set to the MIME type of the posted format)
* Delete: HTTP DELETE /<entity type name>/<entity id>
* <format> can be json, xml etc.
* Permission checking is done with the standard Drupal access and permission
  system on a Drupal user basis.
* Authentication can be achieved via HTTP Basic Authentication (see the
  restws_auth_basic submodule that performs a user login from HTTP headers) or
  via standard Drupal cookies and session handling.

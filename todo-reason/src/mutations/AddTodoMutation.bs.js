// Generated by BUCKLESCRIPT VERSION 6.0.3, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var ReasonRelay = require("reason-relay/src/ReasonRelay.bs.js");
var Caml_exceptions = require("bs-platform/lib/js/caml_exceptions.js");
var AddTodoMutation_graphql$MywWebapp = require("../__generated__/AddTodoMutation_graphql.bs.js");

var MutationFailed = Caml_exceptions.create("AddTodoMutation-MywWebapp.MutationFailed");

var Mutation = ReasonRelay.MakeCommitMutation(/* module */[/* node */AddTodoMutation_graphql$MywWebapp.node]);

var UseMutation = ReasonRelay.MakeUseMutation(/* module */[/* node */AddTodoMutation_graphql$MywWebapp.node]);

var use = UseMutation[/* use */0];

var commitMutation = Mutation[/* commitMutation */0];

var Mutation$1 = /* module */[
  /* Operation */0,
  /* Mutation */Mutation,
  /* UseMutation */UseMutation,
  /* use */use,
  /* commitMutation */commitMutation
];

function sharedUpdater(store, user, newEdge) {
  var userProxy = ReasonRelay.RecordSourceSelectorProxy[/* get */2](store, ReasonRelay.makeDataId(user.id));
  var conn = userProxy !== undefined ? ReasonRelay.ConnectionHandler[/* getConnection */0](Caml_option.valFromOption(userProxy), "TodoList_todos", undefined) : undefined;
  if (conn !== undefined) {
    return ReasonRelay.ConnectionHandler[/* insertEdgeAfter */3](Caml_option.valFromOption(conn), newEdge, undefined);
  } else {
    return /* () */0;
  }
}

var tempID = /* record */[/* contents */0];

function incrementTempId(param) {
  tempID[0] = tempID[0] + 1 | 0;
  return /* () */0;
}

function commit(environment, text, user) {
  incrementTempId(/* () */0);
  return Curry._6(commitMutation, environment, {
              input: {
                text: text,
                userId: user.userId,
                clientMutationId: String(tempID[0])
              }
            }, (function (store) {
                incrementTempId(/* () */0);
                var id = "client:newTodo" + String(tempID[0]);
                var node = ReasonRelay.RecordSourceSelectorProxy[/* create */0](store, ReasonRelay.makeDataId(id), "Todo");
                ReasonRelay.RecordProxy[/* setValueString */16](ReasonRelay.RecordProxy[/* setValueString */16](node, text, "text", undefined), id, "id", undefined);
                var newEdge = ReasonRelay.RecordSourceSelectorProxy[/* create */0](store, ReasonRelay.makeDataId("client:newEdge:" + String(tempID[0])), "TodoEdge");
                ReasonRelay.RecordProxy[/* setLinkedRecord */14](newEdge, node, "node", undefined);
                sharedUpdater(store, user, newEdge);
                var userProxy = ReasonRelay.RecordSourceSelectorProxy[/* get */2](store, ReasonRelay.makeDataId(user.id));
                if (userProxy !== undefined) {
                  var userProxy$1 = Caml_option.valFromOption(userProxy);
                  var maybeTotalCount = ReasonRelay.RecordProxy[/* getValueInt */8](userProxy$1, "totalCount", undefined);
                  if (maybeTotalCount !== undefined) {
                    ReasonRelay.RecordProxy[/* setValueInt */18](userProxy$1, maybeTotalCount + 1 | 0, "totalCount", undefined);
                    return /* () */0;
                  } else {
                    throw [
                          MutationFailed,
                          "Could not find totalCount."
                        ];
                  }
                } else {
                  throw [
                        MutationFailed,
                        "Failed to retrieve userProxy."
                      ];
                }
              }), undefined, (function (store) {
                var payload = ReasonRelay.RecordSourceSelectorProxy[/* getRootField */4](store, "addTodo");
                if (payload !== undefined) {
                  var match = ReasonRelay.RecordProxy[/* getLinkedRecord */2](Caml_option.valFromOption(payload), "todoEdge", undefined);
                  if (match !== undefined) {
                    return sharedUpdater(store, user, Caml_option.valFromOption(match));
                  } else {
                    return /* () */0;
                  }
                } else {
                  return /* () */0;
                }
              }), /* () */0);
}

exports.MutationFailed = MutationFailed;
exports.Mutation = Mutation$1;
exports.sharedUpdater = sharedUpdater;
exports.tempID = tempID;
exports.incrementTempId = incrementTempId;
exports.commit = commit;
/* Mutation Not a pure module */

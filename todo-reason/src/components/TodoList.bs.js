// Generated by BUCKLESCRIPT VERSION 6.0.3, PLEASE EDIT WITH CARE
'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReasonRelay = require("reason-relay/src/ReasonRelay.bs.js");
var Todo$MywWebapp = require("./Todo.bs.js");
var ReasonRelayUtils = require("reason-relay/src/ReasonRelayUtils.bs.js");
var MarkAllTodosMutation$MywWebapp = require("../mutations/MarkAllTodosMutation.bs.js");
var TodoList_user_graphql$MywWebapp = require("../__generated__/TodoList_user_graphql.bs.js");

var UseFragment = ReasonRelay.MakeUseFragment(/* module */[/* fragmentSpec */TodoList_user_graphql$MywWebapp.node]);

function use(fRef) {
  return Curry._1(UseFragment[/* use */0], fRef);
}

var UserFragment = /* module */[
  /* Operation */0,
  /* UseFragment */UseFragment,
  /* use */use
];

function TodoList(Props) {
  var userRef = Props.user;
  var user = Curry._1(UseFragment[/* use */0], userRef);
  var environment = ReasonRelay.useEnvironmentFromContext(/* () */0);
  var handleMarkAllChange = function (e) {
    var complete = e.currentTarget.checked;
    var match = user.todos;
    if (match == null) {
      return /* () */0;
    } else {
      MarkAllTodosMutation$MywWebapp.commit(environment, complete, match, user);
      return /* () */0;
    }
  };
  return React.createElement("section", {
              className: "main"
            }, React.createElement("input", {
                  className: "toggle-all",
                  checked: user.totalCount === user.completedCount,
                  type: "checkbox",
                  onChange: handleMarkAllChange
                }), React.createElement("label", {
                  htmlFor: "toggle-all"
                }, "Mark all as complete"), React.createElement("ul", {
                  className: "todo-list"
                }, $$Array.map((function (node) {
                        return React.createElement(Todo$MywWebapp.make, {
                                    user: user,
                                    todo: node,
                                    key: node.id
                                  });
                      }), ReasonRelayUtils.collectConnectionNodesFromNullable(user.todos))));
}

var make = TodoList;

exports.UserFragment = UserFragment;
exports.make = make;
/* UseFragment Not a pure module */

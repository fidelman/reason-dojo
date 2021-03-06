// Generated by BUCKLESCRIPT VERSION 3.1.4, PLEASE EDIT WITH CARE
'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var ReactSimpleMaps = require("react-simple-maps");
var Fetcher$MyProjectName = require("./Fetcher.bs.js");

function make(height, width, projectionConfig, style, children) {
  return ReasonReact.wrapJsForReason(ReactSimpleMaps.ComposableMap, {
              height: height,
              width: width,
              projectionConfig: {
                scale: projectionConfig.scale,
                rotation: projectionConfig.rotation
              },
              style: style
            }, children);
}

var ComposableMap = /* module */[/* make */make];

function make$1(center, disablePanning, children) {
  return ReasonReact.wrapJsForReason(ReactSimpleMaps.ZoomableGroup, {
              center: center,
              disablePanning: disablePanning
            }, children);
}

var ZoomableGroup = /* module */[/* make */make$1];

function make$2(geography, children) {
  return ReasonReact.wrapJsForReason(ReactSimpleMaps.Geographies, {
              geography: geography
            }, children);
}

var Geographies = /* module */[/* make */make$2];

function make$3(geography, projection, style, children) {
  return ReasonReact.wrapJsForReason(ReactSimpleMaps.Geography, {
              geography: geography,
              projection: projection,
              style: style
            }, children);
}

var Geography = /* module */[/* make */make$3];

function make$4(children) {
  return ReasonReact.wrapJsForReason(ReactSimpleMaps.Markers, (function () {
                return { };
              }), children);
}

var Markers = /* module */[/* make */make$4];

function make$5(marker, children) {
  return ReasonReact.wrapJsForReason(ReactSimpleMaps.Marker, {
              marker: {
                coordinates: marker.coordinates
              }
            }, children);
}

var Marker = /* module */[/* make */make$5];

function make$6(children) {
  return ReasonReact.wrapJsForReason(ReactSimpleMaps.Annotations, (function () {
                return { };
              }), children);
}

var Annotations = /* module */[/* make */make$6];

function make$7(subject, dx, dy, strokeWidth, children) {
  return ReasonReact.wrapJsForReason(ReactSimpleMaps.Annotation, {
              subject: subject,
              dx: dx,
              dy: dy,
              strokeWidth: strokeWidth
            }, children);
}

var Annotation = /* module */[/* make */make$7];

var component = ReasonReact.reducerComponent("Map");

function make$8() {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */(function (self) {
              var fetch = function () {
                return Fetcher$MyProjectName.fetchGet("https://immense-river-25513.herokuapp.com/locations", (function (data) {
                              Curry._1(self[/* send */3], /* Update */[data]);
                              setTimeout(fetch, 5000);
                              return /* () */0;
                            }));
              };
              fetch(/* () */0);
              return Fetcher$MyProjectName.fetchPost("https://immense-river-25513.herokuapp.com/add-location", "fidelman");
            }),
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              return React.createElement("div", {
                          style: {
                            margin: "0 auto",
                            maxWidth: "980",
                            width: "100%"
                          }
                        }, ReasonReact.element(/* None */0, /* None */0, make(551, 980, {
                                  scale: 205,
                                  rotation: /* tuple */[
                                    -11,
                                    0,
                                    0
                                  ]
                                }, {
                                  height: "auto",
                                  width: "100%"
                                }, /* array */[ReasonReact.element(/* None */0, /* None */0, make$1(/* tuple */[
                                            0,
                                            20
                                          ], true, /* array */[
                                            ReasonReact.element(/* None */0, /* None */0, make$2("/world-50m.json", /* array */[(function (geographies, projection) {
                                                          return $$Array.mapi((function (i, geography) {
                                                                        return ReasonReact.element(/* Some */[String(i)], /* None */0, make$3(geography, projection, {
                                                                                        default: {
                                                                                          outline: "none",
                                                                                          fill: "#ECEFF1",
                                                                                          stroke: "#607D8B",
                                                                                          strokeWidth: "0.75"
                                                                                        },
                                                                                        hover: {
                                                                                          outline: "none",
                                                                                          fill: "#607D8B",
                                                                                          stroke: "#607D8B",
                                                                                          strokeWidth: "0.75"
                                                                                        },
                                                                                        pressed: {
                                                                                          outline: "none",
                                                                                          fill: "#FF5722",
                                                                                          stroke: "#607D8B",
                                                                                          strokeWidth: "0.75"
                                                                                        }
                                                                                      }, /* array */[]));
                                                                      }), geographies);
                                                        })])),
                                            ReasonReact.element(/* None */0, /* None */0, make$4(/* array */[$$Array.mapi((function (i, user) {
                                                              var match = user.location;
                                                              return ReasonReact.element(/* Some */[String(i)], /* None */0, make$5({
                                                                              coordinates: /* tuple */[
                                                                                match[1],
                                                                                match[0]
                                                                              ]
                                                                            }, /* array */[React.createElement("circle", {
                                                                                    cx: "0",
                                                                                    cy: "0",
                                                                                    fill: "red",
                                                                                    r: "3"
                                                                                  })]));
                                                            }), self[/* state */1])])),
                                            ReasonReact.element(/* None */0, /* None */0, make$6(/* array */[$$Array.mapi((function (i, user) {
                                                              var match = user.location;
                                                              return ReasonReact.element(/* Some */[String(i)], /* None */0, make$7(/* tuple */[
                                                                              match[1],
                                                                              match[0]
                                                                            ], -30, 30, 1, /* array */[React.createElement("text", undefined, user.username)]));
                                                            }), self[/* state */1])]))
                                          ]))])));
            }),
          /* initialState */(function () {
              return /* array */[];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, _) {
              return /* Update */Block.__(0, [action[0]]);
            }),
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.ComposableMap = ComposableMap;
exports.ZoomableGroup = ZoomableGroup;
exports.Geographies = Geographies;
exports.Geography = Geography;
exports.Markers = Markers;
exports.Marker = Marker;
exports.Annotations = Annotations;
exports.Annotation = Annotation;
exports.component = component;
exports.make = make$8;
/* component Not a pure module */

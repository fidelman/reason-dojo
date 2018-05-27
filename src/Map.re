/* module Style = {

}; */

module ComposableMap = {
  [@bs.deriving abstract]
  type projectionConfigT= {
    scale: int,
    rotation: (int, int, int)
  };

  [@bs.deriving abstract]
  type props = {
    height: int,
    width: int,
    projectionConfig: projectionConfigT,
    style: ReactDOMRe.Style.t
  };

  [@bs.module "react-simple-maps"]
  external composableMap : ReasonReact.reactClass = "ComposableMap";
  let make = (~height, ~width, ~projectionConfig, ~style, children) => {
    ReasonReact.wrapJsForReason(
      ~reactClass=composableMap,
      ~props=props(
        ~height,
        ~width,
        ~projectionConfig=projectionConfigT(~scale=scale(projectionConfig), ~rotation=rotation(projectionConfig)),
        ~style
      ),
      children
    );
  };
};

module ZoomableGroup = {
  [@bs.deriving abstract]
  type props = {
    center: (int, int),
    disablePanning: bool
  };
  [@bs.module "react-simple-maps"]
  external zoomableGroup : ReasonReact.reactClass = "ZoomableGroup";
  let make = (~center, ~disablePanning, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=zoomableGroup,
      ~props=props(
        ~center,
        ~disablePanning
      ),
      children
    )
};

module Geographies = {
  [@bs.deriving abstract]
  type props = {
    geography: string
  };

  [@bs.module "react-simple-maps"]
  external geographies : ReasonReact.reactClass = "Geographies";
  let make = (~geography, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=geographies,
      ~props=props(
        ~geography
      ),
      children
    )
};

module Geography = {
  type geographyT;
  type projectionT;
  
  [@bs.deriving abstract]
  type props = {
    geography: geographyT,
    projection: projectionT,
    style: ReactDOMRe.Style.t
  };

  [@bs.module "react-simple-maps"]
  external geographyJs : ReasonReact.reactClass = "Geography";
  let make = (~geography, ~projection, ~style, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=geographyJs,
      ~props=props(
        ~geography,
        ~projection,
        ~style
      ),
      children
    )
}

let component = ReasonReact.statelessComponent("Map");
let make = (_children) => {
  ...component,
  render: _self =>
    <div>
      <ComposableMap
        width={980}
        height={551}
        projectionConfig={ComposableMap.projectionConfigT(
          ~scale=205,
          ~rotation=(-11, 0, 0)
        )}
        style={ReactDOMRe.Style.make(
          ~width="100%",
          ~height="auto",
        ())}
      >
        <ZoomableGroup
          center={(0, 20)}
          disablePanning={true}
        >
          <Geographies geography="/static/world-50m.json">

          </Geographies>
        </ZoomableGroup>
      </ComposableMap>
    </div>,
};
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

static const std::string fdepl_string = R"(
import "ADASISv3Messages.fidl"

define org.adasis.v3.Spec for typeCollection org.adasis.v3.Messages
{
    MaxPaths = 56

    enumeration ProfileType {
        Node {
            InterpolationType = Spot
        }
        Probability {
            InterpolationType = Step
        }
        HeadingChange {
            InterpolationType = Spot
        }
        LaneModel {
            InterpolationType = Spot
        }
        LaneConnectivity {
            InterpolationType = Spot
        }
        LinearObjects {
            InterpolationType = Spot
        }
        LanesGeometry {
            InterpolationType = Spot
        }
        LaneWidth{
            InterpolationType = Step
        }
        RoadGeometry{
            InterpolationType = Spot
        }
        NumberOfLanesPerDirection {
            InterpolationType = Step
        }
        ComplexIntersection {
            InterpolationType = Step
        }
        LinkIdentifier {
            InterpolationType = Step
        }
        FunctionalRoadClass {
            InterpolationType = Step
        }
        RouteNumberTypes {
            InterpolationType = Step
        }
        FormOfWay {
            InterpolationType = Step
        }
        RoadAccessibility {
            InterpolationType = Step
        }
        AccessRestriction {
            InterpolationType = Step
        }
        OvertakingRestriction {
            InterpolationType = Step
        }
        Tunnel {
            InterpolationType = Step
        }
        Bridge {
            InterpolationType = Step
        }
        DividedRoad {
            InterpolationType = Step
        }
        Curvature {
            InterpolationType = Special
        }
        Slope {
            InterpolationType = Special
        }
        BuiltUpArea {
            InterpolationType = Step
        }
        InTown {
            InterpolationType = Step
        }
        Surface {
            InterpolationType = Step
        }
        TrafficSign {
            InterpolationType = Spot
        }
        TrafficLight {
            InterpolationType = Spot
        }
        SpecialSituation {
            InterpolationType = Spot
        }
        EffectiveSpeedLimit {
            InterpolationType = Step
        }
        AverageSpeed {
            InterpolationType = Step
        }
        FlowSpeed {
            InterpolationType = Step
        }
        RoadCondition {
            InterpolationType = Step
        }
        Weather {
            InterpolationType = Step
        }
        LocationObject {
            InterpolationType = Spot
        }
        PartOfCalculatedRoute {
            InterpolationType = Step
        }
        CountryCode {
            InterpolationType = Step
        }
        RegionCode {
            InterpolationType = Step
        }
        DrivingSide {
            InterpolationType = Step
        }
        UnitSystem {
            InterpolationType = Step
        }
        VersionProtocol {
            InterpolationType = Step
        }
        VersionHardware {
            InterpolationType = Step
        }
        VersionMap {
            InterpolationType = Step
        }
        MapAge {
            InterpolationType = Step
        }
        MapProvider {
            InterpolationType = Step
        }
        MapStatus {
            InterpolationType = Step
        }
        SystemStatus {
            // Global only, no meaningful interpolation!
            InterpolationType = Step
        }
        TimeZoneOffset {
            InterpolationType = Step
        }
        AbsoluteVehiclePosition {
            // Global only, no meaningful interpolation!
            InterpolationType = Step
        }

        // custom ProfileTypes
        MapMatchingStatus {
            InterpolationType = Step
        }
        AdminRoadClass {
            InterpolationType = Step
        }
        RoadSideBarrier {
            InterpolationType = Spot
        }
        RoadReferenceLine {
            InterpolationType = Spot
        }
        Landmark {
            InterpolationType = Spot
        }
        VersionInfo {
            InterpolationType = Step
        }
        MovableBridge {
            InterpolationType = Step
        }
        Unknown {
            InterpolationType = Spot
        }
    }

    struct ProfileEntry {
        instanceId {
            IsOptional = true
        }
        direction {
            IsOptional = true
        }
    }

    // Tags for message structures.
    struct AdasisMessageBase {
        Tag = 1
    }
    struct PositionMessage {
        Tag = 2
    }
    struct ProfileMessage {
        Tag = 4
      }
      struct GlobalDataMessage {
        Tag = 5
      }
      struct ProfileControlMessage {
         Tag = 6
      }
      struct PathControlMessage {
         Tag = 7
      }
      
      // Tags for profile value structures.
      struct ProfileValue {
         Tag = 100
      }
      struct UInt32ProfileValue {
         Tag = 101
      }
      struct Int32ProfileValue {
         Tag = 102
      }
      struct UInt64ProfileValue {
         Tag = 103
      }
      struct FloatProfileValue {
         Tag = 104
      }
      struct BooleanProfileValue {
         Tag = 105
      }
      struct YesNoUnknownProfileValue {
         Tag = 111
      }
      struct FormOfWayProfileValue {
         Tag = 112
      }
      struct DrivingSideProfileValue {
         Tag = 113
      }
      struct UnitSystemProfileValue {
         Tag = 114
      }
      struct SpecialSituationProfileValue {
         Tag = 115
      }
      struct RoadConditionProfileValue {
         Tag = 116
      }
      struct WeatherProfileValue {
         Tag = 117
      }
      struct MapProviderProfileValue {
         Tag = 118
      }
      struct MapStatusProfileValue {
         Tag = 119
      }
      struct NodeProfileValue {
         Tag = 151
      }
      struct SystemStatusProfileValue {
         Tag = 152
      }
      struct AbsoluteVehiclePositionProfileValue {
         Tag = 153
      }
      struct SurfaceConditionProfileValue {
         Tag = 154
      }
      struct SpeedProfileValue {
         Tag = 155
      }
      struct LaneModelValue {
         Tag = 156
      }
      struct LaneConnectivityValue {
         Tag = 157
      }
      struct LinearObjectDefinitionValue {
         Tag = 158
      }
      struct LanesGeometryProfileValue {
         Tag = 159
      }
      struct RoadGeometryProfileValue {
         Tag = 160
      }
      struct TrafficLightProfileValue {
         Tag = 161
      }
      struct EffectiveSpeedLimit {
         Tag = 162
      }
      struct LocationObject {
         Tag = 163
      }
      struct RegionCodeValue {
         Tag = 164
            value {
            MaxSize = 3
               Inline = true
         }
      }
      struct ExtendedSpeedLimitValue {
         Tag = 165
            conditions {
            MaxSize = 5
         }
      }
      struct TrafficSignValue {
         Tag = 166
            panels {
            MaxSize = 5
         }
      }
      struct OffsetFloatProfileValue {
         Tag = 500
      }
      struct ConditionalRestrictionProfileValue {
         Tag = 501
      }
      
      // Tags for Condition structures
      struct Condition {
         Tag = 200
      }
      struct ConditionNumeric {
         Tag = 201
      }
      struct ConditionVehicleType {
         Tag = 202
      }
      struct ConditionLoad {
         Tag = 203
      }
      struct ConditionTimeOfDay {
         Tag = 204
      }
      struct ConditionWeather {
         Tag = 205
      }
      struct ConditionFuzzyTime {
         Tag = 206
      }
      struct ConditionTurnDirection {
         Tag = 207
      }
      
      // Tags for Daimler structures
      // Tags for profile value structures
      struct VersionInfoProfileValue {
         Tag = 1000
      }
      
      struct MapMatchingStatusProfileValue {
         Tag = 1002
      }
      
      struct UInt8ProfileValue {
         Tag = 1004
      }
      
      struct RoadSideBarrierProfileValue {
         Tag = 1005
      }
      
      struct RoadReferenceLineProfileValue {
         Tag = 1006
      }
      
      struct LandmarkProfileValue {
         Tag = 1007
      }
      
      // Tags for LandmarkObjectDetails structures
      struct LandmarkObjectDetails {
         Tag = 1008
      }
      struct LandmarkObjectSignDetails {
         Tag = 1009
      }
      struct LandmarkObjectPoleDetails {
         Tag = 1010
      }
      struct LandmarkObjectPerpendicularWallDetails {
         Tag = 1011
      }
      })";

static const std::string input =
        "package org.adasis.v3\n"
        "\n"
        "typeCollection Messages {\n"
        "    version {\n"
        "        major 1\n"
        "        minor 0\n"
        "    }\n"

        "typedef Angle is Float\n"
        "typedef Distance is UInt32\n"
        "typedef InstanceId is UInt32\n"
        "typedef LaneIdx is UInt8\n"
        "typedef LinearObjId is UInt32\n"
        "typedef Offset is UInt32\n"
        "typedef PathId is UInt32\n"
        "typedef Probability is Float\n"
        "typedef SignLocationMask is UInt16\n"
        "typedef Timestamp is UInt64\n"
        "typedef VehicleSpeed is Float\n"

        "<**\n"
        "@description : text foo\n"
        "@param: NotAvalable - not available\n"
        "@param : Valid - valid\n"
        "**>\n"
        "enumeration Availability {\n"
        "    NotAvailable\n"
        "    Valid\n"
        "}\n"
        "enumeration ChangeMode {\n"
        "    Create\n"
        "    Update\n"
        "    Delete\n"
        "}\n"
        "enumeration ConditionType {\n"
        "    conditionTypeUnknown\n"
        "    conditionTypeVehicle\n"
        "    conditionTypeLoad\n"
        "    conditionTypeTimeOfDay\n"
        "    conditionTypeDaysOfWeek\n"
        "    conditionTypeWeight\n"
        "    conditionTypeTurnDirection\n"
        "    conditionTypeWeather\n"
        "    conditionTypeFuzzyTime\n"
        "}\n"
        "enumeration CurveType {\n"
        "    NotPresent\n"
        "    Polyline\n"
        "    BezierSpline\n"
        "}\n"
        "enumeration DrivingSide {\n"
        "    RightHandDriving = 0\n"
        "    LeftHandDriving = 1\n"
        "}\n"
        "enumeration EffectiveSpeedLimitType {\n"
        "    Unknown\n"
        "    Implicit\n"
        "    ExplicitOnTrafficSign\n"
        "    ExplicitNight\n"
        "    ExplicitDay\n"
        "    ExplicitTimeOrDay\n"
        "    ExplicitRain\n"
        "    ExplicitSnow\n"
        "    ExplicitFog\n"
        "}\n"
        "enumeration FormOfWay {\n"
        "    Unknown = 0\n"
        "    ControlledAccess = 1\n"
        "    MultipleCarriageWay = 2\n"
        "    SingleCarriageWay = 3\n"
        "    RoundaboutCircle = 4\n"
        "    SpecialTrafficFigure = 5\n"
        "    ReservedA = 6\n"
        "    ReservedB = 7\n"
        "    ParallelRoad = 8\n"
        "    RampOnControlledAccess = 9\n"
        "    RampNotOnControlledAccess = 10\n"
        "    FrontageRoad = 11\n"
        "    CarPark = 12\n"
        "    Service = 13\n"
        "    PedestrianZone = 14\n"
        "    NotAvailable = 15\n"
        "}\n"
        "enumeration FuzzyTime {\n"
        "    Unknown\n"
        "    Day\n"
        "    Night\n"
        "}\n"
        "enumeration GuidanceMode {\n"
        "    guidanceInactive\n"
        "    guidanceForUser\n"
        "    guidanceAutomatic\n"
        "}\n"
        "enumeration LaneArrowMarking {\n"
        "    None = 0\n"
        "    Straight = 1\n"
        "    SlightRight = 2\n"
        "    Right = 4\n"
        "    HardRight = 8\n"
        "    UTurn = 16\n"
        "    HardLeft = 32\n"
        "    Left = 64\n"
        "    SlightLeft = 128\n"
        "    NA = -1\n"
        "}\n"
        "<**\n"
        "@param : X_NO_FULLMATCH will be returned when the input is no full match\n"
        "@param : X_NO_INPUT will be returned when the property 'input' is empty\n"
        "@param : X_NO_HISTORY will be returned when there is no history available to remove a \n"
        "         character. Hhappens when the operation setInput() is used to \n"
        "         initialize the input to an arbitrary value.\n"
        "**>\n"
        "enumeration LaneTransition {\n"
        "    None\n"
        "    Opening\n"
        "    Closing\n"
        "    Merging\n"
        "    Splitting\n"
        "}\n"
        "enumeration LaneTypeFlags {\n"
        "    Unknown = 0\n"
        "    Normal = 1\n"
        "    Exit = 2\n"
        "    Entry = 4\n"
        "    Auxiliary = 8\n"
        "    Emergency = 16\n"
        "    RestrictedForbidden = 32\n"
        "    RestrictedUsable = 64\n"
        "    HOV = 128\n"
        "    Express = 256\n"
        "    Reversible = 512\n"
        "    Slow = 1024\n"
        "    DrivableShoulder = 2048\n"
        "    TurnOrSuicide = 4096\n"

        "    // Daimler change\n"
        "    SoftShoulder = 8192\n"
        "    EmergencyBay = 16384\n"
        "}\n"
        "enumeration LateralPosition {\n"
        "    Unknown = 0\n"
        "    Right = 1\n"
        "    Left = 2\n"
        "    Above = 4\n"
        "    Surface = 8\n"
        "}\n"
        "enumeration LineMarking {\n"
        "    Unknown\n"
        "    None\n"
        "    SolidLine\n"
        "    DashedLine\n"
        "    DoubleSolidLine\n"
        "    DoubleDashedLine\n"
        "    LeftSolidRightDashed\n"
        "    RightSolidLeftDashed \n"
        "    DashedBlocks\n"
        "    ShadedArea\n"
        "    PhysicalDivider\n"
        "}\n"
        "enumeration LineMarkingColour {\n"
        "    None\n"
        "    Other\n"
        "    White\n"
        "    Yellow\n"
        "    Orange\n"
        "    Red\n"
        "    Blue\n"
        "}\n"
        "enumeration LinearObjectType {\n"
        "    Centerline\n"
        "    LaneMarking\n"
        "    Guardrail\n"
        "    Fence\n"
        "    Kerb\n"
        "    Wall\n"
        "}\n"
        "enumeration Load {\n"
        "    loadWaterPolluting\n"
        "    loadExplosive\n"
        "    loadOtherDangerous\n"
        "    loadEmpty\n"
        "    loadSpecial\n"
        "    loadGasses\n"
        "    loadFlammableLiquids\n"
        "    loadFlammableSolids\n"
        "    loadOxidizing\n"
        "    loadToxicInfectious\n"
        "    loadRadioactive\n"
        "    loadCorrosive\n"
        "}\n"
        "enumeration LocationObjectType {\n"
        "    GuidePost\n"
        "}\n"
        "enumeration MapProvider {\n"
        "    provider_Unknown\n"
        "    provider_AND\n"
        "    provider_AutoNavi\n"
        "    provider_HERE\n"
        "    provider_Hyundai\n"
        "    provider_Navinfo\n"
        "    provider_TomTom\n"
        "    provider_Zenrin\n"
        "}\n"
        "enumeration MapStatus {\n"
        "    mapNotAvailable\n"
        "    mapLoading\n"
        "    mapAvailable\n"
        "}\n"
        "enumeration MessageType {\n"
        "    Position\n"
        "    Profile\n"
        "    GlobalData\n"
        "    ProfileControl\n"
        "    PathControl\n"
        "}\n"
        "enumeration ProfileType {\n"
        "    Node\n"
        "    Probability\n"
        "    HeadingChange\n"
        "    LaneModel\n"
        "    LaneConnectivity\n"
        "    LinearObjects\n"
        "    LanesGeometry\n"
        "    LaneWidth\n"
        "    RoadGeometry \n"
        "    NumberOfLanesPerDirection\n"
        "    ComplexIntersection\n"
        "    LinkIdentifier\n"
        "    FunctionalRoadClass\n"
        "    RouteNumberTypes\n"
        "    FormOfWay\n"
        "    RoadAccessibility\n"
        "    AccessRestriction\n"
        "    OvertakingRestriction\n"
        "    Tunnel\n"
        "    Bridge\n"
        "    DividedRoad\n"
        "    Curvature\n"
        "    Slope\n"
        "    BuiltUpArea\n"
        "    InTown\n"
        "    Surface\n"
        "    TrafficSign\n"
        "    TrafficLight\n"
        "    SpecialSituation\n"
        "    EffectiveSpeedLimit\n"
        "    ExtendedSpeedLimit\n"
        "    AverageSpeed\n"
        "    FlowSpeed\n"
        "    RoadCondition\n"
        "    Weather\n"
        "    LocationObject\n"
        "    PartOfCalculatedRoute\n"
        "    CountryCode\n"
        "    RegionCode\n"
        "    DrivingSide\n"
        "    UnitSystem\n"
        "    VersionProtocol\n"
        "    VersionHardware\n"
        "    VersionMap\n"
        "    MapAge\n"
        "    MapProvider\n"
        "    MapStatus\n"
        "    SystemStatus\n"
        "    TimeZoneOffset\n"
        "    AbsoluteVehiclePosition\n"

        "    // Daimler change\n"
        "    MapMatchingStatus       // Data type: MapMatchingStatus, Interpolation: Step\n"
        "    AdminRoadClass          // Data type: UInt8, Interpolation: Step\n"
        "    RoadSideBarrier         // Data type: RoadSideBarrierProfileValue\n"
        "    RoadReferenceLine       // Data type: RoadReferenceLineProfileValue\n"
        "    Landmark                // Data type: LandmarkProfileValue\n"
        "    VersionInfo             // Data type: VersionInfoProfileValue, Interpolation: Step\n"
        "    MovableBridge           // Data type: Boolean, Interpolation: Step\n"
        "    Unknown\n"
        "}\n"
        "enumeration Quality {\n"
        "    Unknown\n"
        "    NotAvailable\n"
        "    Value1\n"
        "    Value2\n"
        "    Value3\n"
        "    Value4\n"
        "    Value5\n"
        "}\n"

        "enumeration RelativeDirection {\n"
        "    None\n"
        "    Both\n"
        "    AlongPathDirection\n"
        "    AgainstPathDirection\n"
        "}\n"
        "enumeration RightOfWay {\n"
        "    Unknown\n"
        "    MustYield\n"
        "    HasRightOfWay\n"
        "}\n"
        "enumeration RoadAccessFlags {\n"
        "    PassengerCars = 1\n"
        "    Pedestrians = 2\n"
        "    Bus = 4\n"
        "    Delivery = 8\n"
        "    Emergency = 16\n"
        "    Taxi = 32\n"
        "    ThroughTraffic = 64\n"
        "    Trucks = 128\n"
        "    Bicycles = 256      // Daimler change\n"
        "}\n"
        "enumeration RoadCondition {\n"
        "    Unknown\n"
        "    Clear\n"
        "    Wet\n"
        "    Snowy\n"
        "    Icy\n"
        "    Slippery\n"
        "    Dirt\n"
        "}\n"
        "enumeration SignType {\n"
        "    Unknown = 255\n"
        "    LeftBend = 10\n"
        "    RightBend = 9\n"
        "    DoubleBendLeftFirst = 14\n"
        "    DoubleBendRightFirst = 13\n"
        "    CurvyRoad = 17\n"
        "    SteepDescent = 68\n"
        "    SteepAscent = 67\n"
        "    CarriageWayNarrows = 40\n"
        "    CarriageWayNarrowsLeft = 42\n"
        "    CarriageWayNarrowsRight = 41\n"
        "    SwingBridge = 89\n"
        "    RiverBank = 29\n"
        "    RiverBankLeft = 30\n"
        "    UnevenRoad = 69\n"
        "    Hump = 70\n"
        "    Dip = 71\n"
        "    SlipperyRoad = 66\n"
        "    FallingRocksRight = 62\n"
        "    FallingRocksLeft = 61\n"
        "    Pedestrians = 50\n"
        "    PedestrianCrossing = 51\n"
        "    Children = 52\n"
        "    SchoolZone = 53\n"
        "    Cyclists = 54\n"
        "    DomesticAnimalsCrossing = 4 \n"
        "    WildAnimalsCrossing = 5\n"
        "    RoadWorks = 6\n"
        "    LightSignals = 31\n"
        "    DangerousIntersection = 22\n"
        "    Intersection = 35\n"
        "    IntersectionWithPriorityToTheRight = 37\n"
        "    IntersectionWithMinorRoad = 36 \n"
        "    TwoWayTraffic = 55\n"
        "    TafficCongestion = 75\n"
        "    RailwayCrossingWithGates = 56\n"
        "    RailwayCrossingWithoutGates = 57\n"
        "    TramWay = 59\n"
        "    RailwayCrossing = 58\n"
        "    Danger = 0\n"
        "    GiveWay = 32\n"
        "    Stop = 33\n"
        "    PriorityRoad = 34\n"
        "    PriorityForOncomingTraffic = 82 \n"
        "    PriorityOverOncomingTraffic = 81\n"
        "    OvertakingProhibited = 46\n"
        "    OvertakingByGoodsVehiclesProhibited = 20 \n"
        "    SpeedLimit = 87\n"
        "    EndOfAllProhibitions = 79\n"
        "    EndOfSpeedLimit = 88\n"
        "    EndOfProhibitionOnOvertaking = 47 \n"
        "    EndOfProhibitionOnOvertakingForGoodsVehicles = 21 \n"
        "    DirectionToTheRight = 38\n"
        "    DirectionToTheLeft = 39\n"
        "    PassRightSide = 3\n"
        "    PassLeftOrRightSide = 1\n"
        "    PassLeftSide = 2\n"
        "    BeginningOfBuiltUpArea = 77 \n"
        "    EndOfBuiltUpArea = 83\n"
        "    Tunnel = 24\n"
        "    ResidentialArea = 7 \n"
        "    EndOfResidentialArea = 8 \n"
        "    LaneMergeRight = 44\n"
        "    LaneMergeLeft = 43\n"
        "    ProtectedPassingEnd = 48\n"
        "    HumpbackBridge = 28\n"
        "    VariableSignMechanicElements = 65\n"
        "    VariableSignLightElements = 80\n"
        "    FerryTerminal = 25\n"
        "    NarrowBridge = 26\n"
        "    IcyRoad = 73\n"
        "    SteepDropLeft = 63\n"
        "    SteepDropRight = 64\n"
        "    RoadFloods = 72\n"
        "    SideWinds = 74\n"
        "    LaneMergeCenter = 45\n"
        "    HighAccidentArea = 76\n"
        "    AudibleWarning = 78\n"
        "}\n"
        "enumeration SpecialSituationType {\n"
        "    DeadEnd = 248\n"
        "    FerryTerminal = 249\n"
        "    TollBooth = 250\n"
        "    RailroadCrossing = 251\n"
        "    PedestrianCrossing = 252\n"
        "    SpeedBump = 253\n"
        "}\n"
        "enumeration SpeedLimitSource {\n"
        "    Unknown\n"
        "    Implicit\n"
        "    Explicit\n"
        "}\n"
        "enumeration SurfaceCondition {\n"
        "    Unknown\n"
        "    PavedRigid\n"
        "    PavedFlexible\n"
        "    Blocks\n"
        "    Gravel\n"
        "    Dirt\n"
        "}\n"
        "enumeration TrafficLightLongitudinalPosition {\n"
        "    Unknown\n"
        "    BeforeIntersection\n"
        "    AfterIntersection\n"
        "}\n"
        "enumeration TrafficLightState {\n"
        "    Unknown\n"
        "    Invalid\n"
        "    Off\n"
        "    Green\n"
        "    Yellow\n"
        "    Red\n"
        "}\n"
        "enumeration UnitOfSpeed {\n"
        "    KpH\n"
        "    MpH\n"
        "}\n"
        "enumeration Weather {\n"
        "    Unknown\n"
        "    NoSpecial\n"
        "    Sunshine\n"
        "    Rain\n"
        "    Fog\n"
        "    Snow\n"
        "    Ice\n"
        "    StrongWind\n"
        "}\n"
        "enumeration YesNoUnknown {\n"
        "    Unknown\n"
        "    Yes\n"
        "    No\n"
        "}\n"
        "struct Vector {\n"
        "    Float x\n"
        "    Float y\n"
        "    Float z\n"
        "}\n"
        "struct Speed {\n"
        "    UInt8 value\n"
        "    UnitOfSpeed unit\n"
        "}\n"
        "struct WGS84Point {\n"
        "    Int32 latitude\n"
        "    Int32 longitude\n"
        "    Int32 altitude\n"
        "}\n"
        "struct VehiclePosition {\n"
        "    WGS84Point position // Daimler change: WGS84Point is member of VehiclePosition\n"
        "    Timestamp timestamp\n"
        "    Float heading\n"
        "}\n"
        "struct Position {\n"
        "    PathId pathId\n"
        "    Offset offset\n"
        "    Distance accuracy\n"
        "    Int32 deviation\n"
        "    VehicleSpeed speed\n"
        "    Angle relativeHeading\n"
        "    Probability probability\n"
        "    LaneIdx currentLane\n"
        "    PathId preferredPath\n"
        "}\n"
        "struct AdasisMessageBase polymorphic {\n"
        "}\n"
        "struct PositionMessage extends AdasisMessageBase {\n"
        "    Timestamp timestamp\n"
        "    Timestamp positionAge\n"
        "    Position [] positions\n"
        "}\n"
        "struct ProfileValue polymorphic {\n"
        "}\n"
        "struct ProfileEntry {\n"
        "    InstanceId instanceId\n"
        "    Boolean isRetransmission\n"
        "    ChangeMode change\n"
        "    Float confidence\n"
        "    PathId pathId\n"
        "    LaneIdx [] laneNumbers\n"
        "    RelativeDirection direction\n"
        "    Offset offset\n"
        "    Offset endOffset\n"
        "    Boolean endOffsetFinal\n"
        "    ProfileType type\n"
        "    Availability available\n"
        "    ProfileValue value\n"
        "}\n"
        "struct ProfileMessage extends AdasisMessageBase {\n"
        "    ProfileEntry [] profiles\n"
        "}\n"
        "struct GlobalData {\n"
        "    ProfileType type\n"
        "    Availability available\n"
        "    ProfileValue value\n"
        "}\n"
        "struct GlobalDataMessage extends AdasisMessageBase {\n"
        "    GlobalData [] data\n"
        "}\n"
        "struct ProfileControl {\n"
        "    PathId pathId\n"
        "    Offset offset\n"
        "}\n"
        "struct ProfileControlMessage extends AdasisMessageBase {\n"
        "    ProfileControl [] values\n"
        "}\n"
        "struct PathControl {\n"
        "    PathId Id\n"
        "    PathId parentId\n"
        "    Offset offset\n"
        "}\n"
        "struct PathControlMessage extends AdasisMessageBase {\n"
        "    PathId idFirst\n"
        "    PathId idLast\n"
        "    PathControl [] values\n"
        "}\n"
        "struct MessageOnBus {\n"
        "    UInt8 cyclicCounter\n"
        "    MessageType type\n"
        "    AdasisMessageBase message\n"
        "}\n"
        "struct UInt32ProfileValue extends ProfileValue {\n"
        "    UInt32 value\n"
        "}\n"
        "struct Int32ProfileValue extends ProfileValue {\n"
        "    Int32 value\n"
        "}\n"
        "struct UInt64ProfileValue extends ProfileValue {\n"
        "    UInt64 value\n"
        "}\n"
        "struct FloatProfileValue extends ProfileValue {\n"
        "    Float value\n"
        "}\n"
        "struct BooleanProfileValue extends ProfileValue {\n"
        "    Boolean value\n"
        "}\n"
        "struct YesNoUnknownProfileValue extends ProfileValue {\n"
        "    YesNoUnknown value\n"
        "}\n"
        "struct FormOfWayProfileValue extends ProfileValue {\n"
        "    FormOfWay value\n"
        "}\n"
        "struct DrivingSideProfileValue extends ProfileValue {\n"
        "    DrivingSide value\n"
        "}\n"
        "struct UnitSystemProfileValue extends ProfileValue {\n"
        "    UnitOfSpeed value\n"
        "}\n"
        "struct SpecialSituationProfileValue extends ProfileValue {\n"
        "    SpecialSituationType value\n"
        "}\n"
        "struct RoadConditionProfileValue extends ProfileValue {\n"
        "    RoadCondition value\n"
        "}\n"
        "struct WeatherProfileValue extends ProfileValue {\n"
        "    Weather value\n"
        "}\n"
        "struct MapProviderProfileValue extends ProfileValue {\n"
        "    MapProvider value\n"
        "}\n"
        "struct MapStatusProfileValue extends ProfileValue {\n"
        "    MapStatus value\n"
        "}\n"
        "struct OffsetFloatEntry {\n"
        "    Offset offset\n"
        "    Float value\n"
        "}\n"
        "struct OffsetFloatProfileValue extends ProfileValue {\n"
        "    OffsetFloatEntry [] entries\n"
        "}\n"
        "struct NodeArm {\n"
        "    PathId subPath\n"
        "    Probability probability\n"
        "    Angle turnAngle\n"
        "    Boolean isComplexIntersection\n"
        "    RightOfWay rightOfWay\n"
        "}\n"
        "struct NodeProfileValue extends ProfileValue {\n"
        "    NodeArm [] arms\n"
        "}\n"
        "struct SystemStatusProfileValue extends ProfileValue {\n"
        "    GuidanceMode guidance\n"
        "    Boolean simulating\n"
        "}\n"
        "struct AbsoluteVehiclePositionProfileValue extends ProfileValue {\n"
        "    VehiclePosition position\n"
        "}\n"
        "struct SurfaceConditionProfileValue extends ProfileValue {\n"
        "    Quality general\n"
        "    SurfaceCondition surface\n"
        "}\n"
        "struct SpeedProfileValue extends ProfileValue {\n"
        "    Speed value\n"
        "}\n"
        "struct LaneInfo {\n"
        "    UInt8 laneNumber\n"
        "    RelativeDirection direction\n"
        "    LaneTransition transition\n"
        "    UInt32 types\n"
        "    LinearObjId centerline\n"
        "    LinearObjId leftBoundary\n"
        "    LinearObjId rightBoundary\n"
        "}\n"
        "struct LaneModelValue extends ProfileValue {\n"
        "    UInt8 totalNumberOfLanes\n"
        "    LaneInfo [] laneInfos\n"
        "}\n"
        "struct LaneConnectivityPair {\n"
        "    UInt8 initialLaneNumber\n"
        "    PathId initialPath\n"
        "    UInt8 newLaneNumber\n"
        "    PathId newPath\n"
        "}\n"
        "struct LaneConnectivityValue extends ProfileValue {\n"
        "    LaneConnectivityPair [] connectivityPairs\n"
        "}\n"
        "struct LinearObject {\n"
        "    LinearObjId id\n"
        "    LinearObjectType type\n"
        "    LineMarking marking\n"
        "    LineMarkingColour colour\n"
        "}\n"
        "struct LinearObjectDefinitionValue extends ProfileValue {\n"
        "    LinearObject [] linearObjects\n"
        "}\n"
        "struct Curve {\n"
        "    CurveType type\n"
        "    WGS84Point [] points\n"
        "}\n"
        "struct LineGeometry {\n"
        "    LinearObjId idLine\n"
        "    Curve geometry\n"
        "}\n"
        "struct LanesGeometryProfileValue extends ProfileValue {\n"
        "     LineGeometry [] geometries\n"
        "}\n"
        "struct RoadGeometryProfileValue extends ProfileValue {\n"
        "    Curve roadCenterline\n"
        "}\n"
        "struct TrafficLightProfileValue extends ProfileValue {\n"
        "    TrafficLightLongitudinalPosition longitudinalPosition\n"
        "    LateralPosition lateralPosition\n"
        "    Double cycleTime\n"
        "    TrafficLightState currentState\n"
        "    YesNoUnknown turnOnRedAllowed\n"
        "    Vector position\n"
        "    Vector boundingBox\n"
        "}\n"
        "struct EffectiveSpeedLimit extends ProfileValue {\n"
        "    Speed value\n"
        "    EffectiveSpeedLimitType type\n"
        "}\n"
        "struct LocationObject extends ProfileValue {\n"
        "    LocationObjectType type\n"
        "    Int32 lateralOffset\n"
        "    WGS84Point absolutePosition\n"
        "}\n"
        "struct RegionCodeValue extends ProfileValue {\n"
        "    UInt8 [] value\n"
        "}\n"
        "struct Condition polymorphic {\n"
        "    ConditionType type\n"
        "    YesNoUnknown appliesToEgoVehicle\n"
        "}\n"
        "struct ConditionNumeric extends Condition {\n"
        "    UInt32 value\n"
        "}\n"
        "struct ConditionVehicleType extends Condition {\n"
        "    UInt32 vehicleTypeMask\n"
        "}\n"
        "struct ConditionLoad extends Condition {\n"
        "    Load value\n"
        "}\n"
        "struct ConditionTimeOfDay extends Condition {\n"
        "     UInt16 startMinutes\n"
        "     UInt16 endMinutes\n"
        "}\n"
        "struct ConditionWeather extends Condition {\n"
        "    Weather weather\n"
        "}\n"
        "struct ConditionFuzzyTime extends Condition {\n"
        "    FuzzyTime fuzzyTime\n"
        "}\n"
        "struct ConditionTurnDirection extends Condition {\n"
        "    LaneArrowMarking direction\n"
        "}\n"
        "struct ExtendedSpeedLimitValue extends ProfileValue {\n"
        "    Speed value\n"
        "    SpeedLimitSource source\n"
        "    Condition [] conditions\n"
        "}\n"
        "struct TrafficSignValue extends ProfileValue {\n"
        "    SignType type\n"
        "    UInt32 value\n"
        "    SignLocationMask location\n"
        "    Int32 shift\n"
        "    Distance distance\n"
        "    Distance len        // Length of validity given on additional panel.\n"
        "                        // Rename length to len because length is a forbidden keyword\n"
        "    YesNoUnknown vms\n"
        "    Condition [] panels\n"
        "}\n"
        "struct ConditionalRestrictionProfileValue extends ProfileValue {\n"
        "    Boolean allowed\n"
        "    Condition [] conditions\n"
        "}\n"


        "// Z. Daimler data types:\n"
        "// Version of interface: 1.8\n"
        "// Date of last update: 27.07.2018\n"
        "// Important note! Do not use these variable names because they are used already in the generated code as local variables:\n"
        "//   pos, length, indent, strIndent, result, buffer, count, tag, map\n"

        "struct UInt8ProfileValue extends ProfileValue {\n"
        "    UInt8 value\n"
        "}\n"

        "struct RoadReferenceLineProfileValue extends ProfileValue {\n"
        "    LinearObjId idReferenceLine\n"
        "}\n"

        "// Z.0 Version information:\n"
        "struct VersionInfoProfileValue extends ProfileValue {\n"
        "    UInt8 [] aswRelease            // e.g. E006.0\n"
        "    UInt8 [] aswTag                // e.g. HADwas_18.0F04.3\n"
        "    UInt8 [] aswCommit             // e.g. 9045cb3\n"
        "    UInt8 [] bswRelease            // e.g. E006.0 rc3, K matrix 17_25_a0\n"
        "    UInt8 [] hw                    // e.g. B2\n"
        "    UInt8 [] fidl                  // e.g. 1.6\n"
        "}\n"

        "// Z.1 MapMatching status:\n"
        "enumeration MapMatchingStatus {\n"
        "    OffRoadNoCandidates\n"
        "    OffRoadWithCandidates\n"
        "    MapMatched\n"
        "}\n"

        "struct MapMatchingStatusProfileValue extends ProfileValue {\n"
        "    MapMatchingStatus value\n"
        "}\n"

        "// Z.2 Daimler PDU:\n"
        "typedef CRC is UInt32\n"

        "struct PDU_Daimler {\n"
        "    CRC crc\n"
        "    MessageType typeMsg\n"
        "    ProfileType typeProfile    // Used only with Profile and GlobalData messages, else Unknown\n"
        "    UInt32 cyclicCounter\n"
        "    UInt16 payloadLength       // Length of payload (message)\n"
        "    AdasisMessageBase message\n"
        "}\n"

        "struct MessageOnBus_Daimler {\n"
        "    PDU_Daimler [] pdus\n"
        "}\n"

        "// Z.3 RoadSide barrier:\n"
        "struct WGS84Point2D {\n"
        "    Int32 latitude  // East positive, 2^32 is 360 degrees.\n"
        "    Int32 longitude // North positive, 2^32 is 360 degrees.\n"
        "}\n"

        "struct Curve2D {\n"
        "    CurveType type\n"
        "    WGS84Point2D [] points\n"
        "}\n"

        "struct RoadSideBarrier {\n"
        "    Curve2D geometry\n"
        "    UInt16 heightIndicator // 0.1m resolution, [0 .. 6553.5m] above ground\n"
        "}\n"

        "struct RoadSideBarrierProfileValue extends ProfileValue {\n"
        "    RoadSideBarrier [] barriers\n"
        "}\n"

        "// Z.4 Landmark (NDS 2.5.1 FTX LO 1.0):\n"
        "struct Covariance {\n"
        "    UInt16 varianceXX   // Variance for x var(x)\n"
        "    UInt16 varianceYY   // Variance for y var(y)\n"
        "    UInt16 varianceZZ   // Variance for z var(z)\n"
        "    UInt16 varianceXY   // Covariance for xy cov(x,y)\n"
        "}\n"

        "enumeration LandmarkObjectType {\n"
        "    Sign\n"
        "    Pole\n"
        "    PerpendicularWall\n"
        "}\n"

        "enumeration LandmarkObjectSignShape {\n"
        "    Triangle = 0\n"
        "    Rectangle = 1\n"
        "    Round = 2\n"
        "    Octagon = 3\n"
        "    Diamond = 4\n"
        "    CrossBuck = 5\n"
        "    Yield = 6\n"
        "    Ellipse = 7\n"
        "    Other = 8\n"
        "    Unknown = 15\n"
        "}\n"

        "enumeration WarningSign {\n"
        "    GeneralHazard = 0\n"
        "    PassLeftOrRightOfObstacle = 1\n"
        "    PassLeftOfObstacle = 2\n"
        "    PassRightOfObstacle = 3\n"
        "    Cattle = 4\n"
        "    Animals = 5\n"
        "    RoadWorks = 6\n"
        "    LivingStreetEntry = 7\n"
        "    LivingStreetExit = 8\n"
        "    CurveRight = 9\n"
        "    CurveLeft = 10\n"
        "    TruckRollover = 11\n"
        "    FogArea = 12\n"
        "    CurveRightThenLeft = 13\n"
        "    CurveLeftThenRight = 14\n"
        "    TireChainsMandatory = 15\n"
        "    HijackingHotspot = 16\n"
        "    CurvyRoad = 17\n"
        "    ReverseBends = 18\n"
        "    RoundaboutAhead = 19\n"
        "    NoOvertakingForTrucks = 20\n"
        "    NoOvertakingForTrucksEnd = 21\n"
        "    DangerousIntersection = 22\n"
        "    OverPassAhead = 23\n"
        "    Tunnel = 24\n"
        "    FerryTerminal = 25\n"
        "    NarrowBridge = 26\n"
        "    NoIdling = 27\n"
        "    HumpbackBridge = 28\n"
        "    EmbankmentOnTheRight = 29\n"
        "    EmbankmentOnTheLeft = 30\n"
        "    LightSignals = 31\n"
        "    Yield = 32\n"
        "    Stop = 33\n"
        "    PriorityRoad = 34\n"
        "    Intersection = 35\n"
        "    CrossingWithPriorityOverMinorRoad = 36\n"
        "    CrossingWithPriorityToTheRight = 37\n"
        "    BranchToTheRight = 38\n"
        "    BranchToTheLeft = 39\n"
        "    CarriagewayNarrows = 40\n"
        "    CarriagewayNarrowsRight = 41\n"
        "    CarriagewayNarrowsLeft = 42\n"
        "    LaneMergeFromRight = 43\n"
        "    LaneMergeFromLeft = 44\n"
        "    LaneMergeCenter = 45\n"
        "    NoOvertaking = 46\n"
        "    NoOvertakingEnd = 47\n"
        "    ProtectedPassingEnd = 48\n"
        "    ProtectedPassing = 49\n"
        "    Pedestrians = 50\n"
        "    PedestrianCrossing = 51\n"
        "    Children = 52\n"
        "    SchoolZone = 53\n"
        "    Cyclists = 54\n"
        "    TwoWayTraffic = 55\n"
        "    RailroadCrossingWithGates = 56\n"
        "    RailroadCrossingWithoutGates = 57\n"
        "    RailroadCrossing = 58\n"
        "    TramwayCrossing = 59\n"
        "    FallingRocks = 60\n"
        "    FallingRocksOnTheLeft = 61\n"
        "    FallingRocksOnTheRight = 62\n"
        "    SteepDropOnLeft = 63\n"
        "    SteepDropOnRight = 64\n"
        "    SlipperyRoad = 66\n"
        "    SteepIncline = 67\n"
        "    SteepDecline = 68\n"
        "    UnevenRoad = 69\n"
        "    Bump = 70\n"
        "    Dip = 71\n"
        "    RoadFloods = 72\n"
        "    IcyRoad = 73\n"
        "    Wind = 74\n"
        "    TrafficCongestion = 75\n"
        "    HighAccidentArea = 76\n"
        "    CityEntry = 77\n"
        "    AudibleWarning = 78\n"
        "    EndOfAllRestrictions = 79\n"
        "    PriorityOverOncoming = 81\n"
        "    YieldToOncoming = 82\n"
        "    CityExit = 83\n"
        "    VillageAhead = 84\n"
        "    SpeedCamera = 85\n"
        "    TrafficEnforcementCamera = 86\n"
        "    SpeedLimit = 87\n"
        "    SpeedLimitEnd = 88\n"
        "    MovableBridge = 89\n"
        "    SlowDown = 90\n"
        "    IntersectionTRight = 91\n"
        "    IntersectionTLeft = 92\n"
        "    IntersectionTLeftRight = 93\n"
        "    IntersectionY = 94\n"
        "    PriorityRoadEnd = 95\n"
        "    UseLowGear = 96\n"
        "    NoCompressionBraking = 97\n"
        "    WaitingLine = 98\n"
        "    DontStopZone = 99\n"
        "    LaneUsedInBothDirections = 100\n"
        "    HonkingProhibited = 101\n"
        "    FastenSeatBelt = 102\n"
        "    DeadEnd = 103\n"
        "    AdvisorySpeedLimit = 104\n"
        "    SpeedLimitNight = 105\n"
        "    MinimumSpeed = 106\n"
        "    VariableSpeedLimit = 107\n"
        "    Variable = 108\n"
        "    GoodLuck = 254\n"
        "    Unknown = 255\n"
        "}\n"

        "enumeration LandmarkObjectPoleType {\n"
        "    GuardrailPost\n"
        "    LightPole\n"
        "    DelineatorPost\n"
        "    ReflectorPost\n"
        "    GantryPole\n"
        "    SignPost\n"
        "    Other\n"
        "    Unclassified\n"
        "}\n"

        "struct LandmarkObjectDetails polymorphic {\n"
        "}\n"

        "struct LandmarkObjectSignDetails extends LandmarkObjectDetails {\n"
        "    LandmarkObjectSignShape signShape   // Shape of the face of the sign\n"
        "    WarningSign signMeaning             // Meaning of the (warning) sign\n"
        "    UInt16 diameter                     // Diameter of the round sign in cm (0 = has no diameter)\n"
        "    WGS84Point [] boundingBox            // BoundingBox around the sign (vector of relative WGS84 positions)\n"
        "}\n"

        "struct LandmarkObjectPoleDetails extends LandmarkObjectDetails {\n"
        "    WGS84Point polePositionGround       // The point where the pole intersects with the ground it is standing upon (relative WGS84 position)\n"
        "    UInt16 diameter                     // Diameter of the pole at ground in cm\n"
        "    UInt16 height                       // Height of the pole in cm\n"
        "    LandmarkObjectPoleType poleType     // Type of pole\n"
        "}\n"

        "struct LandmarkObjectPerpendicularWallDetails extends LandmarkObjectDetails {\n"
        "    WGS84Point [] boundingBox            // Bounding box around the wall (vector of relative WGS84 positions)\n"
        "}\n"

        "struct LandmarkObject {\n"
        "    LandmarkObjectType objectType       // Sign, Pole, Marking, TrafficLight, PerpendicularWall\n"
        "    Boolean hasCovariance\n"
        "    Covariance covariance               // Covariance for this object\n"
        "    LandmarkObjectDetails details       // Landmark object details\n"
        "}\n"

        "struct LandmarkProfileValue extends ProfileValue {\n"
        "    WGS84Point position                 // Absolute WGS84 position of the landmark\n"
        "//      UInt8 confidenceLevel               // Confidence level of the landmark data. Value in the range from 0 to 100.\n"
        "                                        // Confidence is already available as float value in Profile\n"
        "    LandmarkObject [] objects            // Vector of landmark objects\n"
        "}\n"

        "// Z.5 BackChannel (separate MapECU_IF -> maybe own fidl in the future):\n"
        "enumeration BackChannelAction {\n"
        "    None = 0\n"
        "    ResendHorizon = 1   // Resend whole horizon due to e.g. message loss\n"
        "    \n"
        "    // Change MostProbablePath to a dedicated path (via pathId).\n"
        "    // The meaning of pathId=0 is to switch to the path of the second most probable position,\n"
        "    // anyhow it is preferred to get a dedicated path to retain the context\n"
        "    ChangeMPP = 2\n"
        "}\n"

        "struct BackChannelMessage {\n"
        "    UInt16 majorVersion         // Major MapECU interface version. Incompatible change\n"
        "    \n"
        "    // Minor MapECU interface version. Compatible change: e.g. small bugfixes, new field\n"
        "    // at the end of a struct, new enum value, etc.\n"
        "    UInt16 minorVersion\n"
        "    BackChannelAction action\n"
        "    PathId pathId               // Only needed for BackChannelAction = ChangeMPP\n"
        "}\n"
        "}\n";

#endif // CONSTANTS_H

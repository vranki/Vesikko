var component
var vessel

function createVessel(id, lat, lon, type) {
    console.log("CreateVessel " + id + " " + lat + "/" + lon + " type " + type );
    component = Qt.createComponent("Vessel.qml");
    vessel = component.createObject(map);
    vessel.lat = lat;
    vessel.lon = lon;
    vessel.objectName = "vessel-" + id
}

function deleteVessel(id) {

}

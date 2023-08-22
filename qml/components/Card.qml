import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

Pane {
    id: cardRoot

    property int elevation: 1
    property int borderRadius: 10

    background: Rectangle {
        radius: cardRoot.elevation

        layer.enabled: true
        layer.effect: ElevationEffect {
            elevation: cardRoot.elevation
        }
    }
}

import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

Pane {
    id: cardRoot
    width: parent.width * 0.8
    anchors.horizontalCenter: parent.horizontalCenter

    background: Rectangle {
        radius: 10

        layer.enabled: true
        layer.effect: ElevationEffect {
            elevation: 1
        }
    }
}

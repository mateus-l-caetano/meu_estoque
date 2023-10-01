import QtQuick
import QtQuick.Layouts 1.3
import QtQuick.Controls
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Material.impl 2.3

import "../components/"

ColumnLayout {
    signal addItem()
    ListView {
        id: itensListView
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.topMargin: 10
        Layout.bottomMargin: 10
        spacing: 10
        model: estoqueModel
        delegate: Card {
            required property string nome

            width: parent.width * 0.8
            anchors.horizontalCenter: parent.horizontalCenter
            contentChildren: ItemVolumeController {
                itemName: nome
            }
        }
    }

    Button {
        id: floatingButton
        text: "+"
        Layout.alignment: Qt.AlignRight | Qt.AlignBottom
        Layout.rightMargin: 10
        Layout.bottomMargin: 10
        onClicked: addItem()
    }
}

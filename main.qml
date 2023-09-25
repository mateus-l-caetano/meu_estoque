import QtQuick
import QtQuick.Layouts 1.3
import QtQuick.Controls
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Material.impl 2.3

import "qml/components/"

ApplicationWindow {
    required property var estoqueModel

    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    header: ToolBar {
        id: toolbar
        RowLayout {
            anchors.fill: parent
            ToolButton {
                id: drawerButton
                text: "="
                onClicked: {
                    appDrawer.open()
                }
            }

            Label {
                text: "Estoque"
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            Item { width: drawerButton.width }
        }
    }

    Drawer {
        id: appDrawer
        height: parent.height
        ColumnLayout {
            anchors.fill: parent
            spacing: 10
            Card {
                Layout.fillWidth: true
                RowLayout {
                    Text {
                        text: "->"
                    }
                    Text {
                        text: "Estoque"
                    }
                }
            }

            Card {
                elevation: 0
                RowLayout {
                    Text {
                        text: "->"
                    }
                    Text {
                        text: "Cadastrar item"
                    }
                }
            }

            Card {
                elevation: 0
                RowLayout {
                    Text {
                        text: "->"
                    }
                    Text {
                        text: "Detalhes"
                    }
                }
            }


            Item { Layout.fillHeight: true }
        }
    }

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: ListView {
            id: itensListView

            anchors.fill: parent
            anchors.topMargin: 10
            anchors.bottomMargin: 10
            spacing: 10
            model: estoqueModel
            delegate: Card {
                required property string nome

                width: parent.width * 0.8
                anchors.horizontalCenter: root.horizontalCenter
                contentChildren: ItemVolumeController {
                    itemName: nome
                }
            }
        }
    }

}

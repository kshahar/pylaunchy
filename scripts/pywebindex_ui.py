# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'pywebindex.ui'
#
# Created: Wed Aug 20 21:36:47 2008
#      by: PyQt4 UI code generator 4.4.2
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(382,424)
        self.verticalLayout = QtGui.QVBoxLayout(Form)
        self.verticalLayout.setObjectName("verticalLayout")
        self.horizontalLayout_2 = QtGui.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        spacerItem = QtGui.QSpacerItem(40,20,QtGui.QSizePolicy.Expanding,QtGui.QSizePolicy.Minimum)
        self.horizontalLayout_2.addItem(spacerItem)
        self.label = QtGui.QLabel(Form)
        self.label.setObjectName("label")
        self.horizontalLayout_2.addWidget(self.label)
        spacerItem1 = QtGui.QSpacerItem(40,20,QtGui.QSizePolicy.Expanding,QtGui.QSizePolicy.Minimum)
        self.horizontalLayout_2.addItem(spacerItem1)
        self.verticalLayout.addLayout(self.horizontalLayout_2)
        self.entriesTable = QtGui.QTableWidget(Form)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Expanding,QtGui.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.entriesTable.sizePolicy().hasHeightForWidth())
        self.entriesTable.setSizePolicy(sizePolicy)
        self.entriesTable.setObjectName("entriesTable")
        self.verticalLayout.addWidget(self.entriesTable)
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        spacerItem2 = QtGui.QSpacerItem(40,20,QtGui.QSizePolicy.Expanding,QtGui.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem2)
        self.addEntryButton = QtGui.QPushButton(Form)
        self.addEntryButton.setObjectName("addEntryButton")
        self.horizontalLayout.addWidget(self.addEntryButton)
        spacerItem3 = QtGui.QSpacerItem(58,17,QtGui.QSizePolicy.Expanding,QtGui.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem3)
        self.removeEntryButton = QtGui.QPushButton(Form)
        self.removeEntryButton.setObjectName("removeEntryButton")
        self.horizontalLayout.addWidget(self.removeEntryButton)
        spacerItem4 = QtGui.QSpacerItem(40,20,QtGui.QSizePolicy.Expanding,QtGui.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem4)
        self.verticalLayout.addLayout(self.horizontalLayout)
        self.forceDatabaseRebuildBox = QtGui.QCheckBox(Form)
        self.forceDatabaseRebuildBox.setObjectName("forceDatabaseRebuildBox")
        self.verticalLayout.addWidget(self.forceDatabaseRebuildBox)

        self.retranslateUi(Form)
        QtCore.QObject.connect(self.addEntryButton,QtCore.SIGNAL("clicked()"),Form.addEntry_clicked)
        QtCore.QObject.connect(self.removeEntryButton,QtCore.SIGNAL("clicked()"),Form.removeEntry_clicked)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        Form.setWindowTitle(QtGui.QApplication.translate("Form", "Form", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("Form", "PyWebIndex - Launch links from index pages", None, QtGui.QApplication.UnicodeUTF8))
        self.entriesTable.clear()
        self.entriesTable.setColumnCount(2)
        self.entriesTable.setRowCount(0)
        headerItem = QtGui.QTableWidgetItem()
        headerItem.setText(QtGui.QApplication.translate("Form", "Name", None, QtGui.QApplication.UnicodeUTF8))
        self.entriesTable.setHorizontalHeaderItem(0,headerItem)
        headerItem1 = QtGui.QTableWidgetItem()
        headerItem1.setText(QtGui.QApplication.translate("Form", "Index URL", None, QtGui.QApplication.UnicodeUTF8))
        self.entriesTable.setHorizontalHeaderItem(1,headerItem1)
        self.addEntryButton.setToolTip(QtGui.QApplication.translate("Form", "Add a new entry", None, QtGui.QApplication.UnicodeUTF8))
        self.addEntryButton.setText(QtGui.QApplication.translate("Form", "+", None, QtGui.QApplication.UnicodeUTF8))
        self.removeEntryButton.setToolTip(QtGui.QApplication.translate("Form", "Remove the selected entry", None, QtGui.QApplication.UnicodeUTF8))
        self.removeEntryButton.setText(QtGui.QApplication.translate("Form", "-", None, QtGui.QApplication.UnicodeUTF8))
        self.forceDatabaseRebuildBox.setToolTip(QtGui.QApplication.translate("Form", "Rebuild database even if settings were not changed", None, QtGui.QApplication.UnicodeUTF8))
        self.forceDatabaseRebuildBox.setText(QtGui.QApplication.translate("Form", "Force database rebuild", None, QtGui.QApplication.UnicodeUTF8))


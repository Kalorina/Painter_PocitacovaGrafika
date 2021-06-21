#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets>
#include "ui_ObjectLayers.h"
#include "ObjectClass.h"

class ObjectLayers : public QDialog
{
	Q_OBJECT

public:
	ObjectLayers(QWidget* parent = Q_NULLPTR) : QDialog(parent), layersUi(new Ui::Dialog)
	{
		layersUi->setupUi(this);
	}

	int getLayer() { return layersUi->spinBoxLayer->value(); }
	void setTable(QVector<Object> objects) {

		layersUi->tableWidget->setRowCount(objects.size());
		layersUi->tableWidget->setColumnCount(2);

		for (int i = 0; i < objects.size(); i++)
		{

			QTableWidgetItem* meal1 = new QTableWidgetItem();
			meal1->setText(objects[i].getType());

			layersUi->tableWidget->setItem(i, 0, meal1);
			QString l = QString::number(objects[i].getZbuffer() + 1);
			QTableWidgetItem* layer = new QTableWidgetItem();
			layer->setText(l);
			layersUi->tableWidget->setItem(i, 1, layer);

		}
	}

private:
	Ui::Dialog* layersUi;

	QColor color;
};
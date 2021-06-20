#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets>
#include "ui_ObjectLayers.h"

class ObjectLayers : public QDialog
{
	Q_OBJECT

public:
	ObjectLayers(QWidget* parent = Q_NULLPTR) : QDialog(parent), layersUi(new Ui::Dialog)
	{
		layersUi->setupUi(this);
	}

	int getLayer() { return layersUi->spinBoxLayer->value(); }

private:
	Ui::Dialog* layersUi;
};
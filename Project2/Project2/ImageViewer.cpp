#include "ImageViewer.h"

ImageViewer::ImageViewer(QWidget* parent)
	: QMainWindow(parent), ui(new Ui::ImageViewerClass)
{
	ui->setupUi(this);

	//ui->menuBar->setDisabled(true);

	int width = 500;
	int height = 500;
	QString name = "Scatch";
	openNewTabForImg(new ViewerWidget(name, QSize(width, height)));
	ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);

	ui->pushButtonPolygone->setDisabled(true);
	ui->pushButtonCircle->setDisabled(true);
	ui->pushButtonBezier->setDisabled(true);
	ui->pushButtonSquere->setDisabled(true);
	ui->pushButtonLine->setDisabled(true);

	ui->groupBox_2->setDisabled(true);
}

//ViewerWidget functions
ViewerWidget* ImageViewer::getViewerWidget(int tabId)
{
	QScrollArea* s = static_cast<QScrollArea*>(ui->tabWidget->widget(tabId));
	if (s) {
		ViewerWidget* vW = static_cast<ViewerWidget*>(s->widget());
		return vW;
	}
	return nullptr;
}
ViewerWidget* ImageViewer::getCurrentViewerWidget()
{
	return getViewerWidget(ui->tabWidget->currentIndex());
}

// Event filters
bool ImageViewer::eventFilter(QObject* obj, QEvent* event)
{
	if (obj->objectName() == "ViewerWidget") {
		return ViewerWidgetEventFilter(obj, event);
	}
	return false;
}

//ViewerWidget Events
bool ImageViewer::ViewerWidgetEventFilter(QObject* obj, QEvent* event)
{
	ViewerWidget* w = static_cast<ViewerWidget*>(obj);

	if (!w) {
		return false;
	}

	if (event->type() == QEvent::MouseButtonPress) {
		ViewerWidgetMouseButtonPress(w, event);
	}
	else if (event->type() == QEvent::MouseButtonRelease) {
		ViewerWidgetMouseButtonRelease(w, event);
	}
	else if (event->type() == QEvent::MouseMove) {
		ViewerWidgetMouseMove(w, event);
	}
	else if (event->type() == QEvent::Leave) {
		ViewerWidgetLeave(w, event);
	}
	else if (event->type() == QEvent::Enter) {
		ViewerWidgetEnter(w, event);
	}
	else if (event->type() == QEvent::Wheel) {
		ViewerWidgetWheel(w, event);
	}

	return QObject::eventFilter(obj, event);
}
void ImageViewer::ViewerWidgetMouseButtonPress(ViewerWidget* w, QEvent* event)
{
	QMouseEvent* e = static_cast<QMouseEvent*>(event);

	if (drawingActive)
	{
		if (e->button() == Qt::LeftButton)
		{
			points.append(e->pos());
			//w->setPixel(e->pos().x(), e->pos().y(), color);
			//qDebug() << points;
		}
		if (e->button() == Qt::RightButton && !polygoneMode && !circleMode && !bezierCurveMode && !squereMode && points.size() == 2)
		{
			//line
			Object object = Object(points, color, objects.size() + 1, "line");
			objects.append(object);
			w->draw(object.getPoints(), color, ui->comboBoxAlg->currentText(), ui->comboBoxInterpolation->currentText(), ui->checkBoxFill->isChecked());
			drawingActive = false;
			objectDrawn = true;
		}
		if (e->button() == Qt::RightButton && !polygoneMode && !bezierCurveMode && !squereMode && circleMode && points.size() == 2)
		{
			//Circle
			Object object = Object(points, color, objects.size() + 1, "circle");
			objects.append(object);
			w->drawCircle(object.getPoints(), color, ui->comboBoxAlg->currentText(), ui->checkBoxFill->isChecked());
			drawingActive = false;
			objectDrawn = true;
		}
		if (e->button() == Qt::RightButton && !polygoneMode && !bezierCurveMode && squereMode && points.size() == 2)
		{
			//squere
			QPointF C = QPointF(points[1].x(), points[0].y());
			QPointF D = QPointF(points[0].x(), points[1].y());
			QVector<QPointF> newPoints;
			newPoints.append(points[0]); newPoints.append(C); newPoints.append(points[1]); newPoints.append(D);
			points = newPoints;
			Object object = Object(points, color, objects.size() + 1, "square");
			objects.append(object);
			w->draw(object.getPoints(), color, ui->comboBoxAlg->currentText(), ui->comboBoxInterpolation->currentText(), ui->checkBoxFill->isChecked());
			drawingActive = false;
			objectDrawn = true;
		}
		if (e->button() == Qt::RightButton && polygoneMode && !squereMode && !bezierCurveMode)
		{
			//polygone
			Object object = Object(points, color, objects.size() + 1, "polygone");
			objects.append(object);
			w->draw(object.getPoints(), color, ui->comboBoxAlg->currentText(), ui->comboBoxInterpolation->currentText(), ui->checkBoxFill->isChecked());
			drawingActive = false;
			objectDrawn = true;
		}
		if (e->button() == Qt::RightButton && !polygoneMode && !squereMode && bezierCurveMode)
		{
			//curve
			Object object = Object(points, color, objects.size() + 1, "curve");
			objects.append(object);
			w->drawBezierCurve(object.getPoints(), color);
			drawingActive = false;
			objectDrawn = true;
		}
	}
	else
	{
		if (e->button() == Qt::LeftButton)
		{
			if (objectDrawn)
			{
				movingObject = true;
				lastMovePoint = e->pos();
			}
		}
	}
}
void ImageViewer::ViewerWidgetMouseButtonRelease(ViewerWidget* w, QEvent* event)
{
	QMouseEvent* e = static_cast<QMouseEvent*>(event);

	if (e->button() == Qt::LeftButton)
	{
		movingObject = false;
	}
}
void ImageViewer::ViewerWidgetMouseMove(ViewerWidget* w, QEvent* event)
{
	if (currentLayer == -1)
	{
		return;
	}

	Object currentObject = objects[currentLayer];
	QVector<QPointF> points = currentObject.getPoints();

	QMouseEvent* e = static_cast<QMouseEvent*>(event);
	
	QPointF vector = QPointF(0, 0);

	if (movingObject)
	{
		clearImage();
		vector.setX(e->pos().x() - lastMovePoint.x());
		vector.setY(e->pos().y() - lastMovePoint.y());

		for (int i = 0; i < points.size(); i++)
		{
			points[i] = QPointF(points[i].x() + vector.x(), points[i].y() + vector.y());

		}
		lastMovePoint = e->pos();

		currentObject.setPoints(points);
		objects.replace(currentLayer, currentObject);
		updateImage();
	}
}
void ImageViewer::ViewerWidgetLeave(ViewerWidget* w, QEvent* event)
{
}
void ImageViewer::ViewerWidgetEnter(ViewerWidget* w, QEvent* event)
{
}
void ImageViewer::ViewerWidgetWheel(ViewerWidget* w, QEvent* event)
{
	if (currentLayer == -1)
	{
		return;
	}

	Object currentObject = objects[currentLayer];
	QVector<QPointF> points = currentObject.getPoints();

	QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);

	double factorDown = 0.75;
	double factorUp = 1.25;

	clearImage();

	if (wheelEvent->angleDelta().y() > 0)
	{
		for (int i = 1; i < points.size(); i++)
		{
			points[i] = QPointF(factorUp * (points[i].x() - points[0].x()) + points[0].x(), factorUp * (points[i].y() - points[0].y()) + points[0].y());

		}
	}

	if (wheelEvent->angleDelta().y() < 0)
	{
		for (int i = 1; i < points.size(); i++)
		{
			points[i] = QPointF(factorDown * (points[i].x() - points[0].x()) + points[0].x(), factorDown * (points[i].y() - points[0].y()) + points[0].y());

		}
	}

	currentObject.setPoints(points);
	objects.replace(currentLayer, currentObject);
	updateImage();
}

//ImageViewer Events
void ImageViewer::closeEvent(QCloseEvent* event)
{
	if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation", "Are you sure you want to exit?", QMessageBox::Yes | QMessageBox::No))
	{
		event->accept();
	}
	else {
		event->ignore();
	}
}

//Image functions
void ImageViewer::openNewTabForImg(ViewerWidget* vW)
{
	QScrollArea* scrollArea = new QScrollArea;
	scrollArea->setWidget(vW);

	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidgetResizable(true);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	vW->setObjectName("ViewerWidget");
	vW->installEventFilter(this);

	QString name = vW->getName();

	ui->tabWidget->addTab(scrollArea, name);
}
bool ImageViewer::openImage(QString filename)
{
	QFileInfo fi(filename);

	QString name = fi.baseName();
	openNewTabForImg(new ViewerWidget(name, QSize(0, 0)));
	ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);

	ViewerWidget* w = getCurrentViewerWidget();

	QImage loadedImg(filename);
	return w->setImage(loadedImg);
}
bool ImageViewer::saveImage(QString filename)
{
	QFileInfo fi(filename);
	QString extension = fi.completeSuffix();
	ViewerWidget* w = getCurrentViewerWidget();

	QImage* img = w->getImage();
	return img->save(filename, extension.toStdString().c_str());
}
void ImageViewer::clearImage()
{
	ViewerWidget* w = getCurrentViewerWidget();
	w->clear();
}
void ImageViewer::setBackgroundColor(QColor color)
{
	ViewerWidget* w = getCurrentViewerWidget();
	w->clear(color);
}

//Tabs slots
void ImageViewer::on_tabWidget_tabCloseRequested(int tabId)
{
	ViewerWidget* vW = getViewerWidget(tabId);
	delete vW; //vW->~ViewerWidget();
	ui->tabWidget->removeTab(tabId);
}
void ImageViewer::drawPoints()
{
}
void ImageViewer::on_actionRename_triggered()
{
	if (!isImgOpened()) {
		msgBox.setText("No image is opened.");
		msgBox.setIcon(QMessageBox::Information);
		msgBox.exec();
		return;
	}
	ViewerWidget* w = getCurrentViewerWidget();
	bool ok;
	QString text = QInputDialog::getText(this, QString("Rename image"), tr("Image name:"), QLineEdit::Normal, w->getName(), &ok);
	if (ok && !text.trimmed().isEmpty())
	{
		w->setName(text);
		ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), text);
	}
}

//Image slots
void ImageViewer::on_actionNew_triggered()
{
	newImgDialog = new NewImageDialog(this);
	connect(newImgDialog, SIGNAL(accepted()), this, SLOT(newImageAccepted()));
	newImgDialog->exec();
}
void ImageViewer::newImageAccepted()
{
	NewImageDialog* newImgDialog = static_cast<NewImageDialog*>(sender());

	int width = newImgDialog->getWidth();
	int height = newImgDialog->getHeight();
	QString name = newImgDialog->getName();
	openNewTabForImg(new ViewerWidget(name, QSize(width, height)));
	ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);

	ui->groupBoxSetUp->setEnabled(true);
}
void ImageViewer::on_actionOpen_triggered()
{
	QString folder = settings.value("folder_img_load_path", "").toString();

	QString fileFilter = "Image data (*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm .*xbm .* xpm);;All files (*)";
	QString fileName = QFileDialog::getOpenFileName(this, "Load image", folder, fileFilter);
	if (fileName.isEmpty()) { return; }

	QFileInfo fi(fileName);
	settings.setValue("folder_img_load_path", fi.absoluteDir().absolutePath());

	if (!openImage(fileName)) {
		msgBox.setText("Unable to open image.");
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.exec();
	}
}
void ImageViewer::on_actionSave_as_triggered()
{
	if (!isImgOpened()) {
		msgBox.setText("No image to save.");
		msgBox.setIcon(QMessageBox::Information);
		msgBox.exec();
		return;
	}
	QString folder = settings.value("folder_img_save_path", "").toString();

	ViewerWidget* w = getCurrentViewerWidget();

	QString fileFilter = "Image data (*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm .*xbm .* xpm);;All files (*)";
	QString fileName = QFileDialog::getSaveFileName(this, "Save image", folder + "/" + w->getName(), fileFilter);
	if (fileName.isEmpty()) { return; }

	QFileInfo fi(fileName);
	settings.setValue("folder_img_save_path", fi.absoluteDir().absolutePath());

	if (!saveImage(fileName)) {
		msgBox.setText("Unable to save image.");
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.exec();
	}
	else {
		msgBox.setText(QString("File %1 saved.").arg(fileName));
		msgBox.setIcon(QMessageBox::Information);
		msgBox.exec();
	}
}
void ImageViewer::on_actionSave_Program_State_triggered()
{
	QString fileName = "ProgramState.txt";

	QFile File(fileName);

	if (File.open(QIODevice::WriteOnly)) {
		QTextStream out(&File);

		out << objects.size() << "\n";

		for (int i = 0; i < objects.size(); i++)
		{
			out << objects[i].getType() << "\n";
			out << objects[i].getColor().red() << "," << objects[i].getColor().green() << "," << objects[i].getColor().blue() << "\n";
			out << objects[i].getZbuffer() << "\n";
			out << objects[i].getNumberOfPoints() << "\n";
			for (int j = 0; j < objects[i].getPoints().size(); j++)
			{
				out << objects[i].getPoints()[j].x() << "," << objects[i].getPoints()[j].y() << "\n";
			}
		}

		File.close();

		qDebug() << "data saved.";
		msgBox.setText("Data did save.");
		msgBox.exec();
	}
	else {
		qDebug() << "file did not open.";
		qDebug() << File.errorString();
		return;
	}
}
void ImageViewer::on_actionOpen_Program_State_triggered()
{
	qDebug() << "Loading Program State";

	QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("txt Files (*.txt);;All files (*.)"));

	if (fileName.isEmpty()) {
		qDebug() << "file is empty";
		return;
	}

	QFileInfo Finfo(fileName);

	if (Finfo.suffix() == "txt") {

		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			return;

		QTextStream in(&file);
		while (!in.atEnd()) {
			QString line = in.readLine();
			data.push_back(line);
		}

		file.close();
	}

	if (!data.isEmpty())
	{
		QMessageBox msgBox;
		msgBox.setText("Data did load.");
		msgBox.exec();
	}

	loadObjects();
	updateImage();
}
void ImageViewer::on_actionClear_triggered()
{
	if (!isImgOpened()) {
		msgBox.setText("No image is opened.");
		msgBox.setIcon(QMessageBox::Information);
		msgBox.exec();
		return;
	}
	clearImage();
}
void ImageViewer::on_actionSet_background_color_triggered()
{
	QColor backgroundColor = QColorDialog::getColor(Qt::white, this, "Select color of background");
	if (backgroundColor.isValid()) {
		setBackgroundColor(backgroundColor);
	}
}

//UI SetUp
void ImageViewer::on_pushButtonDraw_clicked()
{
	drawingActive = true;
	objectDrawn = false;
	points.clear();

	polygoneMode = false;
	circleMode = false;
	bezierCurveMode = false;
	squereMode = false;

	ui->pushButtonPolygone->setEnabled(true);
	ui->pushButtonCircle->setEnabled(true);
	ui->pushButtonBezier->setEnabled(true);
	ui->pushButtonSquere->setEnabled(true);
	ui->pushButtonLine->setEnabled(true);

	ui->groupBox_2->setDisabled(true);
}
void ImageViewer::loadObjects()
{
	objects.clear();
	QString number = data[0];
	int numberOfObjects = number.toInt();

	for (int i = 1; i < data.size(); i++)
	{
		QString type = data[i];
		//qDebug() << data[i];
		if (type == "line")
		{
			Object object;
			object.setType(type);
			QString stringColor = data[1 + i];
			QStringList list = stringColor.split(QLatin1Char(','));
			QColor color;
			color.setRed(list.at(0).toInt()); color.setGreen(list.at(1).toInt()); color.setBlue(list.at(2).toInt());
			object.setColor(color);
			object.setZbuffer(data[i + 2].toInt());
			QVector<QPointF> points;
			for (int j = 0; j < 2; j++)
			{
				QString pointS = data[4 + i + j];
				QStringList list = pointS.split(QLatin1Char(','));
				// list1: [ "x", "y"]
				QPointF point = QPointF(list.at(0).toInt(), list.at(1).toInt());
				points.append(point);
			}
			object.setPoints(points);
			objects.append(object);
		}
		if (type == "circle")
		{
			Object object;
			object.setType(type);
			QString stringColor = data[1 + i];
			QStringList list = stringColor.split(QLatin1Char(','));
			QColor color;
			color.setRed(list.at(0).toInt()); color.setGreen(list.at(1).toInt()); color.setBlue(list.at(2).toInt());
			object.setColor(color);
			object.setZbuffer(data[i + 2].toInt());
			QVector<QPointF> points;
			for (int j = 0; j < 2; j++)
			{
				QString pointS = data[4 + i + j];
				QStringList list = pointS.split(QLatin1Char(','));
				// list1: [ "x", "y"]
				QPointF point = QPointF(list.at(0).toInt(), list.at(1).toInt());
				points.append(point);
			}
			object.setPoints(points);
			objects.append(object);
		}
		if (type == "square")
		{
			Object object;
			object.setType(type);
			QString stringColor = data[1 + i];
			QStringList list = stringColor.split(QLatin1Char(','));
			QColor color;
			color.setRed(list.at(0).toInt()); color.setGreen(list.at(1).toInt()); color.setBlue(list.at(2).toInt());
			object.setColor(color);
			object.setZbuffer(data[i + 2].toInt());
			QVector<QPointF> points;
			for (int j = 0; j < 4; j++)
			{
				QString pointS = data[4 + i + j];
				QStringList list = pointS.split(QLatin1Char(','));
				// list1: [ "x", "y"]
				QPointF point = QPointF(list.at(0).toInt(), list.at(1).toInt());
				points.append(point);
			}
			object.setPoints(points);
			objects.append(object);
		}
		if (type == "polynome")
		{
			Object object;
			object.setType(type);
			QString stringColor = data[1 + i];
			QStringList list = stringColor.split(QLatin1Char(','));
			QColor color;
			color.setRed(list.at(0).toInt()); color.setGreen(list.at(1).toInt()); color.setBlue(list.at(2).toInt());
			object.setColor(color);
			object.setZbuffer(data[i + 2].toInt());
			int numberOfPoints = data[i + 3].toInt();
			QVector<QPointF> points;
			for (int j = 0; j < numberOfPoints; j++)
			{
				QString pointS = data[4 + i + j];
				QStringList list = pointS.split(QLatin1Char(','));
				// list1: [ "x", "y"]
				QPointF point = QPointF(list.at(0).toInt(), list.at(1).toInt());
				points.append(point);
			}
			object.setPoints(points);
			objects.append(object);
		}
		if (type == "curve")
		{
			Object object;
			object.setType(type);
			QString stringColor = data[1 + i];
			QStringList list = stringColor.split(QLatin1Char(','));
			QColor color;
			color.setRed(list.at(0).toInt()); color.setGreen(list.at(1).toInt()); color.setBlue(list.at(2).toInt());
			object.setColor(color);
			object.setZbuffer(data[i + 2].toInt());
			int numberOfPoints = data[i + 3].toInt();
			QVector<QPointF> points;
			for (int j = 0; j < numberOfPoints; j++)
			{
				QString pointS = data[4 + i + j];
				qDebug() << pointS;
				QStringList list = pointS.split(QLatin1Char(','));
				// list: [ "x", "y"]
				QPointF point = QPointF(list.at(0).toInt(), list.at(1).toInt());
				points.append(point);
			}
			object.setPoints(points);
			objects.append(object);
		}
	}

	/*for (int i = 0; i < objects.size(); i++)
	{
		objects[i].print();
	}*/
}
void ImageViewer::on_pushButtonPolygone_clicked()
{
	polygoneMode = true;
	ui->pushButtonPolygone->setDisabled(true);
	ui->pushButtonCircle->setDisabled(true);
	ui->pushButtonBezier->setDisabled(true);
	ui->pushButtonSquere->setDisabled(true);
	ui->pushButtonLine->setDisabled(true);
}
void ImageViewer::on_pushButtonCircle_clicked()
{
	circleMode = true;
	ui->pushButtonPolygone->setDisabled(true);
	ui->pushButtonCircle->setDisabled(true);
	ui->pushButtonBezier->setDisabled(true);
	ui->pushButtonSquere->setDisabled(true);
	ui->pushButtonLine->setDisabled(true);
}
void ImageViewer::on_pushButtonBezier_clicked()
{
	ui->pushButtonPolygone->setDisabled(true);
	ui->pushButtonCircle->setDisabled(true);
	ui->pushButtonBezier->setDisabled(true);
	ui->pushButtonSquere->setDisabled(true);
	ui->pushButtonLine->setDisabled(true);
	bezierCurveMode = true;

	msgBox.setText("Reminder: At least 2 points are required.");
	msgBox.exec();
}
void ImageViewer::on_pushButtonSquere_clicked()
{
	ui->pushButtonPolygone->setDisabled(true);
	ui->pushButtonCircle->setDisabled(true);
	ui->pushButtonBezier->setDisabled(true);
	ui->pushButtonSquere->setDisabled(true);
	ui->pushButtonLine->setDisabled(true);
	squereMode = true;

	msgBox.setText("Reminder: Just 2 points are required.");
	msgBox.exec();
}
void ImageViewer::on_pushButtonLine_clicked()
{
	ui->pushButtonPolygone->setDisabled(true);
	ui->pushButtonCircle->setDisabled(true);
	ui->pushButtonBezier->setDisabled(true);
	ui->pushButtonSquere->setDisabled(true);
	ui->pushButtonLine->setDisabled(true);
}
void ImageViewer::on_pushButtonClear_clicked()
{
	clearImage();

	polygoneMode = false;
	circleMode = false;
	bezierCurveMode = false;
	squereMode = true;

	drawingActive = false;
	objectDrawn = false;

	objects.clear();
	currentLayer = -1;
	points.clear();

	ui->groupBox_2->setDisabled(true);
}

//Object layers
void ImageViewer::on_pushButtonLayer_clicked()
{
	objectLayers = new ObjectLayers(this);
	connect(objectLayers, SIGNAL(accepted()), this, SLOT(objectLayersAccepted()));
	objectLayers->setTable(objects);
	objectLayers->exec();
}
void ImageViewer::on_pushButtonColorLayer_clicked()
{
	int layer = ui->spinBoxLayerColor->value();
	qDebug() << layer;
	currentLayer = layer;
	if (objects.size() < currentLayer)
	{
		msgBox.setText("Wrong layer.");
		msgBox.exec();
		currentLayer = -1;
		return;
	}
	updateColorInLayer(layer, color);
	updateImage();
}
void ImageViewer::on_pushButtonColorPalette_clicked()
{
	QColor color1 = QColorDialog::getColor(Qt::white, this, "Color Palette");
	if (color1.isValid())
	{
		color = color1;
	}
}
void ImageViewer::objectLayersAccepted()
{
	currentLayer = objectLayers->getLayer();
	if (objects.size() < currentLayer)
	{
		msgBox.setText("Wrong layer.");
		msgBox.exec();
		currentLayer = -1;
		return;
	}
	ui->groupBox_2->setEnabled(true);
	updateImage();
}
void ImageViewer::updateImage()
{
	clearImage();

	for (int i = 0; i < objects.size(); i++)
	{
		drawObject(objects[i]);
	}
}
void ImageViewer::drawObject(Object object)
{
	ViewerWidget* w = getCurrentViewerWidget();
	
	if (object.getType() == "circle")
	{
		w->drawCircle(object.getPoints(), object.getColor(), ui->comboBoxAlg->currentText(), ui->checkBoxFill->isChecked());
	}
	else if (object.getType() == "curve")
	{
		w->drawBezierCurve(object.getPoints(), object.getColor());
	}
	else
	{
		w->draw(object.getPoints(), object.getColor(), ui->comboBoxAlg->currentText(), ui->comboBoxInterpolation->currentText(), ui->checkBoxFill->isChecked());
	}
}
void ImageViewer::updateColorInLayer(int layer, QColor color)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (i == layer)
		{
			objects[i].setColor(color);
		}
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i].print();
	}
}
void ImageViewer::updateLayer(int newLayer)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (i == currentLayer)
		{
			objects.insert(newLayer, objects[currentLayer]);
		}
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i].setZbuffer(i+1);
		objects[i].print();
	}
}
void ImageViewer::on_pushButtonChangeLayer_clicked()
{
	int newLayer = ui->spinBoxNewLayer->value();
	qDebug() << newLayer;
	currentLayer = newLayer;
	if (objects.size() < currentLayer)
	{
		msgBox.setText("Wrong layer.");
		msgBox.exec();
		currentLayer = -1;
		return;
	}
	updateLayer(newLayer);
	updateImage();
}

//Transformations
void ImageViewer::on_pushButtonRotate_clicked()
{
	if (currentLayer == -1)
	{
		return;
	}
	Object currentObject = objects[currentLayer];
	QVector<QPointF> points = currentObject.getPoints();
	ViewerWidget* w = getCurrentViewerWidget();
	double degree = ui->spinBoxRotate->value();
	QPoint zero = QPoint(points[0].x(), points[0].y());
	int a, b;

	if (degree >= 0)
	{
		for (int i = 1; i < points.size(); i++)
		{
			a = points[i].x() - zero.x();
			b = points[i].y() - zero.y();
			points[i].setX(a * qCos(-degree * M_PI / 180) - b * qSin(-degree * M_PI / 180) + zero.x());
			points[i].setY(a * qSin(-degree * M_PI / 180) + b * qCos(-degree * M_PI / 180) + zero.y());
		}
	}
	if (degree < 0)
	{
		for (int i = 1; i < points.size(); i++)
		{
			a = points[i].x() - zero.x();
			b = points[i].y() - zero.y();
			points[i].setX(a * qCos(degree * M_PI / 180) + b * qSin(degree * M_PI / 180) + zero.x());
			points[i].setY(-a * qSin(degree * M_PI / 180) + b * qCos(degree * M_PI / 180) + zero.y());
		}
	}

	//qDebug() << points;
	currentObject.setPoints(points);
	objects.replace(currentLayer, currentObject);
	updateImage();

}
void ImageViewer::on_pushButtonScale_clicked()
{
	if (currentLayer == -1)
	{
		return;
	}
	Object currentObject = objects[currentLayer];
	QVector<QPointF> points = currentObject.getPoints();
	ViewerWidget* w = getCurrentViewerWidget();

	double factorX = ui->spinBoxScale_1->value();
	double factorY = ui->spinBoxScale_2->value();

	if (factorX != 0 && factorY != 0)
	{
		for (int i = 1; i < points.size(); i++)
		{
			points[i] = QPoint(factorX * (points[i].x() - points[0].x()) + points[0].x(), factorY * (points[i].y() - points[0].y()) + points[0].y());

		}
	}
	currentObject.setPoints(points);
	objects.replace(currentLayer, currentObject);
	updateImage();
}
void ImageViewer::on_pushButtonShear_clicked()
{
	if (currentLayer == -1)
	{
		return;
	}
	Object currentObject = objects[currentLayer];
	QVector<QPointF> points = currentObject.getPoints();
	ViewerWidget* w = getCurrentViewerWidget();

	double factorX = ui->spinBoxShear->value();

	for (int i = 0; i < points.size() - 1; i++)
	{
		points[i] = QPoint(points[i].x() + factorX * points[i].y(), points[i].y());
	}
	currentObject.setPoints(points);
	objects.replace(currentLayer, currentObject);
	updateImage();
}
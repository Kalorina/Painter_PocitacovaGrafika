#pragma once
#include <QtWidgets>
#include "edgeClass.h"

class ViewerWidget :public QWidget {
	Q_OBJECT
private:
	QString name = "";
	QSize areaSize = QSize(0, 0);
	QImage* img = nullptr;
	QRgb* data = nullptr;
	QPainter* painter = nullptr;

	int** zBuffer = nullptr;
	QColor** fBuffer = nullptr;

public:
	ViewerWidget(QString viewerName, QSize imgSize, QWidget* parent = Q_NULLPTR);
	~ViewerWidget();
	void resizeWidget(QSize size);

	//Image functions
	bool setImage(const QImage& inputImg);
	QImage* getImage() { return img; };
	bool isEmpty();

	//Data functions
	QRgb* getData() { return data; }
	void setPixel(int x, int y, const QColor& color);
	void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);
	bool isInside(int x, int y) { return (x >= 0 && y >= 0 && x < img->width() && y < img->height()) ? true : false; }

	//Get/Set functions
	QString getName() { return name; }
	void setName(QString newName) { name = newName; }

	void setPainter() { painter = new QPainter(img); }
	void setDataPtr() { data = reinterpret_cast<QRgb*>(img->bits()); }

	int getImgWidth() { return img->width(); };
	int getImgHeight() { return img->height(); };

	void drawLineDDA(QPointF startPoint, QPointF endPoint, QColor color, int z);
	void drawCircleDDA(QPointF originPoint, QPointF radiusPoint, QColor color, int z);
	void drawLineBresen(QPointF startPoint, QPointF endPoint, QColor color, int z);
	void drawCircleBresen(QPointF originPoint, QPointF radiusPoint, QColor color, int z);

	void draw(QVector<QPointF> points, int z, QColor color, QString algorithm, QString interpolation, bool fillOn);
	void drawCircle(QVector<QPointF> points, int z, QColor color, QString algorithm, bool fillOn);
	void drawPoints(QVector<QPointF> points, int z);
	void drawBezierCurve(QVector<QPointF> points, int z, QColor color);

	//orezavanie 
	QVector<QPointF> cyrusBeck(QPointF a, QPointF b); //usecka
	QVector<QPointF> sutherlandHodgman(QVector<QPointF> points, int minX); //polygone

	//Vyplnanie farieb
	void scanLine(QVector<QPointF> points, int z, QColor color);
	QVector<Edge> redirectEdgesByY(QVector<Edge> edges);
	QVector<QPointF> sortByYThenByX(QVector<QPointF> points);

	void scanLineTriangle(QVector<QPointF> points, int z, QColor color, QString interpolation);
	QColor nearestNeighbor(QVector<QPointF> points, QPointF p, int z, QColor c1, QColor c2, QColor c3);
	QColor Barycentric(QVector<QPointF> points, QPointF p, int z, QColor c1, QColor c2, QColor c3);
	QColor interpolationPixel(QString interpolation, QVector<QPointF> points, QPointF p, int z, QColor c1, QColor c2, QColor c3);

	//zBuffer
	float interpolationZ(QVector<QPointF> points, QPointF p, QVector<float> zCoordinates);
	void drawBuffer();
	void createBuffers();
	void setPixelZ(int x, int y, int z, QColor color);
	void deleteBuffers();
	void clearBuffers();
	void clear(QColor color = Qt::white);

public slots:
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
};
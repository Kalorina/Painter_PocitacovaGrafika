#pragma once
#include <QtWidgets>

class Object {
private:
	QVector<QPointF> points;
	QColor color;
	int zBuffer;
	QString type; //polygone;circle;triangle;curve;line;
	bool fillOn;

public:
	Object() { points.resize(0); color = QColor("black"); zBuffer = 0; type = ""; fillOn = false; }
	Object(QVector<QPointF> p, QColor c, int z, QString t, bool fill) { points = p; color = c; zBuffer = z; type = t; fillOn = fill; }

	void setPoints(QVector<QPointF> p) { points = p; }
	void setColor(QColor c) { color = c; }
	void setZbuffer(int z) { zBuffer = z; }
	void setType(QString t) { type = t; }
	void setFill(bool fill) { fillOn = fill; }

	QVector<QPointF> getPoints() { return points; }
	QColor getColor() { return color; }
	int getZbuffer() { return zBuffer; }
	QString getType() { return type; }
	bool getFill() { return fillOn; }
	int getNumberOfPoints() { return points.size(); }

	void print() {

		qDebug() << "Object type: " << type;
		qDebug() << "Color: " << color;
		qDebug() << "Fill: " << fillOn;
		qDebug() << "Layer int: " << zBuffer;
		qDebug() << "Points: " << points;
	}
};

#pragma once
#include <QtWidgets>

class Object {
private:
	QVector<QPointF> points;
	QColor color;
	int zBuffer;
	QString type; //polygone;circle;triangle;curve;line;

public:
	Object() { points.resize(0); color= QColor("black"); zBuffer = 0; type = ""; }
	Object(QVector<QPointF> p, QColor c, int z, QString t) { points = p; color = c; zBuffer = z; type = t; }

	void setPoints(QVector<QPointF> p) { points = p; }
	void setColor(QColor c) { color = c; }
	void setZbuffer(int z) { zBuffer = z; }
	void setType(QString t) { type = t; }

	QVector<QPointF> getPoints() { return points; }
	QColor getColor() { return color; }
	int getZbuffer() { return zBuffer; }
	QString getType() { return type; }
	int getNumberOfPoints() { return points.size(); }

	void print() {
		qDebug() << "Points: " << points;
		qDebug() << "Color: " << color;
		qDebug() << "Z buffer int: " << zBuffer;
		qDebug() << "Object type: " << type;
	}
};

#pragma once
#include <QtWidgets>

class Object {
private:
	QVector<QPointF> points;
	int zBuffer;
	QString type; //polygone;circle;triangle;curve;line;

public:
	Object() { points.resize(0); zBuffer = 0; type = ""; }
	Object(QVector<QPointF> p, int z, QString t) { points = p; zBuffer = z; type = t; }

	void setPoints(QVector<QPointF> p) { points = p; }
	void setZbuffer(int z) { zBuffer = z; }
	void setType(QString t) { type = t; }

	QVector<QPointF> getPoints() { return points; }
	int getZbuffer() { return zBuffer; }
	QString getType() { return type; }

	void print() {
		qDebug() << "Points: " << points;
		qDebug() << "Z buffer int: " << zBuffer;
		qDebug() << "Object type: " << type;
	}
};

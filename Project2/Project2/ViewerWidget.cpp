 #include   "ViewerWidget.h"
#include <algorithm>
#include <QtAlgorithms>

ViewerWidget::ViewerWidget(QString viewerName, QSize imgSize, QWidget* parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents);
	setMouseTracking(true);
	name = viewerName;
	if (imgSize != QSize(0, 0)) {
		img = new QImage(imgSize, QImage::Format_ARGB32);
		img->fill(Qt::white);
		resizeWidget(img->size());
		setPainter();
		setDataPtr();
	}
}
ViewerWidget::~ViewerWidget()
{
	delete painter;
	delete img;
}
void ViewerWidget::resizeWidget(QSize size)
{
	this->resize(size);
	this->setMinimumSize(size);
	this->setMaximumSize(size);
}

//Image functions
bool ViewerWidget::setImage(const QImage& inputImg)
{
	if (img != nullptr) {
		delete img;
	}
	img = new QImage(inputImg);
	if (!img) {
		return false;
	}
	resizeWidget(img->size());
	setPainter();
	update();

	return true;
}
bool ViewerWidget::isEmpty()
{
	if (img->size() == QSize(0, 0)) {
		return true;
	}
	return false;
}

//Data function
void ViewerWidget::setPixel(int x, int y, const QColor& color)
{
	if (isInside(x, y)) {
		data[x + y * img->width()] = color.rgb();
	}
}
void ViewerWidget::setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	if (isInside(x, y)) {
		QColor color(r, g, b);
		setPixel(x, y, color);
	}
}

void ViewerWidget::drawLineDDA(QPointF startPoint, QPointF endPoint,QColor color, int z)
{
	QPointF a, b;
	if (startPoint.x() > endPoint.x())
	{
		a = endPoint;
		b = startPoint;
	}
	else
	{
		a = startPoint;
		b = endPoint;
	}

	double deltaX = b.x() - a.x();
	double deltaY = b.y() - a.y();

	double m;
	m = deltaY / deltaX;
	double y = a.y();
	double absM = abs(m);

	if (absM <= 1)
	{
		for (int i = a.x(); i < b.x(); i++)
		{
			setPixelZ(i, y, z, color);
			y = y + m;
		}
	}
	if (absM > 1)
	{
		if (m < -1)
		{
			QPointF c;
			c = a;
			a = b;
			b = c;
		}
		for (int i = a.y(); i < b.y(); i++)
		{
			setPixelZ(int(a.x() + (i - a.y()) / m), i + 1, z, color);
		}
	}
	//update();
	drawBuffer();
}
void ViewerWidget::drawCircleDDA(QPointF originPoint, QPointF radiusPoint, QColor color, int z)
{
	double originX = originPoint.x();
	double originY= originPoint.y();
	double radiusX = radiusPoint.x();
	double radiusY = radiusPoint.y();

	double deltaX = radiusX - originX;
	double deltaY = radiusY - originY;

	double radius = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

	int n = 64;
	double step = 2 * M_PI / n;
	int x, y;
	QPointF a, b;

	for (double i = 0; i <= 2*M_PI; i=i+step)
	{
		a.setX(originX + radius * qCos(i));
		a.setY(originY + radius * qSin(i));
		b.setX(originX + radius * qCos(i + step));
		b.setY(originY + radius * qSin(i + step));

		drawLineDDA(a, b, color,z);

		a.setX(originX + radius * qCos(i));
		a.setY(originY + radius * qSin(i));
		b.setX(originX + radius * qCos(i - step));
		b.setY(originY + radius * qSin(i - step));

		drawLineDDA(a, b, color,z);
	}
}
void ViewerWidget::drawLineBresen(QPointF startPoint, QPointF endPoint, QColor color, int z)
{
	QPointF a, b;
	if (startPoint.x() > endPoint.x())
	{
		a = endPoint;
		b = startPoint;
	}
	else
	{
		a = startPoint;
		b = endPoint;
	}

	int x1 = a.x();
	int y1 = a.y();
	int x2 = b.x();
	int y2 = b.y();
	int y3,x3;

	int dx = x2 - x1;
	int dy = y2 - y1;

	double m;
	m = double(dy) / double(dx);
	
	int p = 2 * dy - dx;
	int k1, k2;

	if (m>0)
	{
		if (m >= 1)
		{
			//riadiaca os y A
			k1 = 2 * dx;
			k2 = 2 * dx - 2 * dy;
			p = 2 * dx - dy;
			
			for (int i = y1; i < y2; i++)
			{
				setPixelZ(x1, i, z, color);
				if (p > 0)
				{
					x1++;
					p = p + k2;
				}
				else
				{
					p = p + k1;
				}
			}
		}
		if (m < 1)
		{
			//riadacia os x A
			k1 = 2 * dy;
			k2 = 2 * dy - 2 * dx;
			p = 2 * dy - dx;

			for (int i = x1; i < x2; i++)
			{
				setPixelZ(i, y1, z, color);
				if (p > 0)
				{
					y1++;
					p = p + k2;
				}
				else
				{
					p = p + k1;
				}
			}
		}
	}
	if (m < 0)
	{
		if (m >= (-1))
		{
			//riadiaca os x B
			k1 = 2 * (y2 - y1);
			k2 = 2 * (y2 - y1) + 2 * (x2 - x1);
			p = 2 * (y2 - y1) + (x2 - x1);
			
			for (int i = x1; i < x2; i++)
			{
				setPixelZ(i, y1, z, color);
				if (p <= 0)
				{
					y1--;
					p = p + k2;
				}
				else
				{
					p = p + k1;
				}
			}
		}
		if (m < -1)
		{
			//riadiaca os y B
			x1 = b.x();
			y1 = b.y();
			x2 = a.x();
			y2 = a.y();

			k1 = 2 * (x2-x1);
			k2 = 2 * (x2 - x1) + 2 * (y2 - y1);
			p = 2 * (x2 - x1) + (y2 - y1);

			for (int i = y1; i < y2; i++)
			{
				setPixelZ(x1, i, z, color);
				if (p <= 0)
				{
					x1--;
					p = p + k2;
				}
				else
				{
					p = p + k1;
				}
			}
		}
	}
	//update();
	drawBuffer();
}
void ViewerWidget::drawCircleBresen(QPointF originPoint, QPointF radiusPoint, QColor color, int z)
{
	int x1 = originPoint.x();
	int y1 = originPoint.y();
	int x2 = radiusPoint.x();
	int y2 = radiusPoint.y();

	int radius = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

	int x, y, p, twoX, twoY;

	p = 1 - radius;
	x = 0;
	y = radius;
	twoX = 3;
	twoY = 2 * radius + 2;

	for (int i = 0; i <= y; i++)
	{
		setPixelZ(i + x1, y + y1, z, color);
		setPixelZ(y + x1, i + y1, z, color);

		setPixelZ(i + x1, y1 - y, z, color);
		setPixelZ(y + x1, y1 - i, z, color);

		setPixelZ(x1 - y, y1 + i, z, color);
		setPixelZ(x1 - i, y1 + y, z, color);

		setPixelZ(x1 - i, y1 - y, z, color);
		setPixelZ(x1 - y, y1 - i, z, color);

		if (p>0)
		{
			p = p - twoY;
			y--;
			twoY -= 2;
		}
		p = p + twoX;
		twoX += 2;
	}
	//update();
	drawBuffer();
}

QVector<QPointF> ViewerWidget::cyrusBeck(QPointF a, QPointF b)
{
	QVector<QPointF> E, edges, points;
	QPointF d, n, w, first, last;
	double t, tl, tu, skalar1, skalar2, x1, y1, x2, y2;

	if ((a.x() > b.x() && a.y() < b.y()) || (a.x() < b.x() && a.y() < b.y()))
	{
		first = a; last = b;
	}
	if ((a.x() < b.x() && a.y() > b.y()) || (a.x() > b.x() && a.y() > b.y()))
	{
		first = b; last = a;
	}

	if (isInside(a.x(),a.y()) || isInside(b.x(),b.y()))
	{
		E.append(QPointF(0, 0)); E.append(QPointF(img->width()-1, 0)); E.append(QPointF(img->width()-1, img->height()-1)); E.append(QPointF(0, img->height()-1));
		
		edges.append(QPointF(E[1] - E[0])); edges.append(QPointF(E[2] - E[1])); edges.append(QPointF(E[3] - E[2])); edges.append(QPointF(E[0] - E[3]));

		tl = 0;
		tu = 1;

		d = QPointF(last.x() - first.x(), last.y() - first.y());

		for (int i = 0; i < edges.size(); i++)
		{
			n = QPointF(-edges[i].y(), edges[i].x());
			w = QPointF(first.x() - E[i].x(), first.y() - E[i].y());

			skalar1 = n.x() * d.x() + n.y() * d.y();
			skalar2 = n.x() * w.x() + n.y() * w.y();

			if (skalar1 != 0)
			{
				t = -skalar2 / skalar1;
				if (skalar1 > 0 && t <= 1)
				{
					//tl = std::max(t, tl);
					if (t>tl)
					{
						tl = t;
					}
				}
				if (skalar1 < 0 && t >= 0)
				{
					//tu = std::min(t, tu);
					if (t<tu)
					{
						tu=t;
					}
				}
			}
		}
		if (tl == 0 && tu == 1)
		{
			a = a;
			b = b;
		}
		else
		{
			if (tl < tu)
			{
				x1 = first.x() + (double)d.x() * tl;
				y1 = first.y() + (double)d.y() * tl;
				a = QPointF(std::round(x1),std::round(y1));

				x2 = first.x() + (double)d.x() * tu;
				y2 = first.y() + (double)d.y() * tu;
				b = QPointF(std::round(x2), std::round(y2));
			}
		}
	}

	//qDebug() << "tl=" << tl << " " << "tu=" << tu;

	points.append(a);
	points.append(b);

	return points;
}
QVector<QPointF> ViewerWidget::sutherlandHodgman(QVector<QPointF> points, int minX)
{
	if (points.isEmpty())
	{
		return points;
	}

	QVector<QPointF> W, V = points;
	QPointF S = V.last(), P;

	for (int i = 0; i < V.size(); i++)
	{
		if (V[i].x() >= minX)
		{
			if (S.x() >= minX)
			{
				W.append(V[i]);
			}
			else
			{
				P = QPointF(minX, S.y() + (minX - S.x()) * (((double)(V[i].y() - S.y())) / ((double)(V[i].x() - S.x()))));
				W.append(P);
				W.append(V[i]);
			}
		}
		else
		{
			if (S.x() >= minX)
			{
				P = QPointF(minX, S.y() + (minX - S.x()) * (((double)(V[i].y() - S.y())) / ((double)(V[i].x() - S.x()))));
				W.append(P);
			}
		}
		S = V[i];
	}
	return W;
}

void ViewerWidget::scanLine(QVector<QPointF> points, int z, QColor color)
{
	Edge e;
	QVector<Edge> edges;
	QVector<Edge> ZAH; //Zoznam Akctivnych Hran
	double f, g, g1, f1, h, y;
	QVector<QVector<Edge>> TH; //Tabulka hran


	for (int i = 0; i < points.size() - 1; i++)
	{
		f = points[i].x();
		g = points[i].y();
		e.setXZ(f); e.setYZ(g);
		f = points[i + 1].x();
		g = points[i + 1].y();
		e.setXK(f); e.setYK(g);
		edges.push_back(e);
	}

	f = points.last().x();
	g = points.last().y();

	f1 = points.first().x();
	g1 = points.first().y();

	e.setXZ(f); e.setYZ(g);
	e.setXK(f1); e.setYK(g1);
	edges.push_back(e);

	edges = redirectEdgesByY(edges);

	QVector<Edge> tempEdges;
	for (int i = 0; i < edges.size(); i++)
	{
		if (edges[i].getYZ() != edges[i].getYK())
		{
			tempEdges.push_back(edges[i]);
		}
	}
	edges = tempEdges;

	for (int i = 0; i < edges.size(); i++)
	{
		double yK = edges[i].getYK() - 1;
		edges[i].setYK(yK);
		edges[i].setCount(0);
	}

	tempEdges.clear();
	for (int i = 0; i < edges.size(); i++)
	{
		if (edges[i].getYZ() != edges[i].getYK())
		{
			tempEdges.push_back(edges[i]);
		}
	}
	edges = tempEdges;

	if (edges.isEmpty())
	{
		return;
	}

	std::sort(edges.begin(), edges.end());

	double yMin = edges[0].getYZ();
	double yMax = -1;

	for (int i = 0; i < edges.size(); i++)
	{
		yMax = std::max(edges[i].getYK(), yMax);
	}

	TH.resize(yMax - yMin + 2);

	for (int i = 0; i < TH.size(); i++)
	{
		for (int j = 0; j < edges.size(); j++)
		{
			edges[j].setDY();
			double x = edges[j].getXZ();
			edges[j].setX(x);
			double w = edges[j].getW();

			double index = edges[j].getYZ() - yMin;

			if (i == (int)std::round(index))
			{
				TH[i].append(edges[j]);
			}
		}
	}

	y = yMin;

	for (int i = 0; i < TH.size(); i++)
	{
		if (!TH[i].isEmpty())
		{
			for (int j = 0; j < TH[i].size(); j++)
			{
				ZAH.push_back(TH[i][j]);
			}
		}

		for (int j = 0; j < ZAH.size(); j++)
		{
			ZAH[j].setCount(1);
		}

		std::sort(ZAH.begin(), ZAH.end());

		for (int j = 0; j < ZAH.size() - 1; j=j+2)
		{
			if (ZAH[j].getX() != ZAH[j + 1].getX())
			{
				for (int k = (int)ZAH[j].getX(); k <= (int)ZAH[j + 1].getX(); k++)
				{
					setPixelZ(k, y, z, color);
				}
			}
		}

		for (int j = 0; j < ZAH.size(); j++)
		{
			double dy = ZAH[j].getDY();
			ZAH[j].setDY(dy - 1);
			double x = ZAH[j].getX();
			double w = ZAH[j].getW();
			ZAH[j].setX(x + w);
		}

		QVector<Edge> filteredZAH;
		for (int j = 0; j < ZAH.size(); j++)
		{
			double dy = ZAH[j].getDY();
			if (dy != 0)
			{
				filteredZAH.push_back(ZAH[j]);
			}
		}
		ZAH = filteredZAH;
		y++;
	}
	//update();
	drawBuffer();
}
QVector<Edge> ViewerWidget::redirectEdgesByY(QVector<Edge> edges)
{
	double xZ, yZ, xK, yK;

	for (int i = 0; i < edges.size(); i++)
	{
		if (edges[i].getYZ() > edges[i].getYK())
		{
			xZ = edges[i].getXK(); yZ = edges[i].getYK();
			xK = edges[i].getXZ(); yK = edges[i].getYZ();

			edges[i].setXZ(xZ); edges[i].setYZ(yZ);
			edges[i].setXK(xK); edges[i].setYK(yK);
		}
	}

	return edges;
}
QVector<QPointF> ViewerWidget::sortByYThenByX(QVector<QPointF> points)
{
	struct myclass {
		bool operator() (QPointF a, QPointF b) {
			return a.y() == b.y() ? a.x() < b.x() : (a.y() < b.y());
		}
	} myobject;

	std::sort(points.begin(), points.end(), myobject);

	return points;
}

void ViewerWidget::scanLineTriangle(QVector<QPointF> points, int z, QColor color, QString interpolation)
{
	points = sortByYThenByX(points);

	QVector<Edge> edges(4);
	Edge a, b, c, d;
	QPointF p; // priesecnik

	QColor c1 = QColor(0, 255, 0);
	QColor c2 = QColor(255, 0, 0);
	QColor c3 = QColor(0, 0, 255);
	
	if ((points[0].y() == points[1].y() && points[1].y() == points[2].y()) || 
		(points[0].x() == points[1].x() && points[1].x() == points[2].x()))
	{
		return;
	}
	if (points[0].y() == points[1].y())
	{
		//spodny troj
		a = Edge(points[0], points[2]);
		b = Edge(points[1], points[2]);
		
	}
	else if (points[1].y() == points[2].y())
	{
		//horny troj
		a = Edge(points[0], points[1]);
		b = Edge(points[0], points[2]);
	}
	else
	{
		double dy = points[2].y() - points[0].y(); 
		double dx = points[2].x() - points[0].x();
		double m = dy / dx;
		double w;
		if (m == 0) { w = 0; } else { w = 1.0 / m; }
		double x = (points[1].y() - points[0].y()) * w + points[0].x();
		p.setX(x);
		p.setY(points[1].y());

		if (points[1].x() > p.x())
		{
			a = Edge(points[0], p);
			b = Edge(points[0], points[1]);

			c = Edge(p, points[2]);
			d = Edge(points[1], points[2]);
		}
		else
		{
			a = Edge(points[0], points[1]);
			b = Edge(points[0], p);

			c = Edge(points[1], points[2]);
			d = Edge(p, points[2]);
		}
	}

	double y = a.getYZ();
	double yMax = b.getYK();
	double x1 = a.getXZ();
	double x2 = b.getXZ();

	while (y < yMax)
	{
		if (x1 != x2)
		{
			for (int i = x1; i < x2; i++)
			{
				QPointF t = QPointF(i, y);
				QColor c = interpolationPixel(interpolation, points, t, z, c1, c2, c3);
				setPixelZ(i, y, z, c);
			}
		}
		x1 += a.getW(); 
		x2 += b.getW();
		y++;
	}

	if (!p.isNull())
	{
		y = c.getYZ();
		yMax = c.getYK();
		x1 = c.getXZ();
		x2 = d.getXZ();

		while (y <= yMax)
		{
			for (int i = x1; i <= x2; i++)
			{
				QPointF t = QPointF(i, y);
				QColor c = interpolationPixel(interpolation, points, t, z, c1, c2, c3);
				setPixelZ(i, y, z, c);
			}
			x1 += c.getW();
			x2 += d.getW();
			y++;
		}
	}
	//update();
	drawBuffer();
}

QColor ViewerWidget::nearestNeighbor(QVector<QPointF> points, QPointF p, int z, QColor c1, QColor c2, QColor c3)
{
	double x = points[0].x() - p.x();
	double y = points[0].y() - p.y();
	double d0 = sqrt(x * x + y * y);

	x = points[1].x() - p.x();
	y = points[1].y() - p.y();
	double d1 = sqrt(x * x + y * y);

	x = points[2].x() - p.x();
	y = points[2].y() - p.y();
	double d2 = sqrt(x * x + y * y);

	QColor color;
	if (d0 < d1 && d0 < d2)
	{
		color = c1;
	}
	if (d1 < d0 && d1 < d0)
	{
		color = c2;
	}
	if (d2 < d0 && d2 < d1)
	{
		color = c3;
	}

	return color;
}
QColor ViewerWidget::Barycentric(QVector<QPointF> points, QPointF p, int z, QColor c1, QColor c2, QColor c3)
{
	points = sortByYThenByX(points);

	QPointF u = QPointF(points[1].x() - points[0].x(), points[1].y() - points[0].y());
	QPointF v = QPointF(points[2].x() - points[0].x(), points[2].y() - points[0].y());
	double nA = u.x() * v.y() - u.y() * v.x();
	double a = sqrt(nA * nA) / 2;

	QPointF u0 = QPointF(points[1].x() - p.x(), points[1].y() - p.y());
	QPointF v0 = QPointF(points[2].x() - p.x(), points[2].y() - p.y());
	double nA0 = u0.x() * v0.y() - u0.y() * v0.x();
	double a0 = sqrt(nA0 * nA0) / 2;

	QPointF u1 = QPointF(points[0].x() - p.x(), points[0].y() - p.y());
	QPointF v1 = QPointF(points[2].x() - p.x(), points[2].y() - p.y());
	double nA1 = u1.x() * v1.y() - u1.y() * v1.x();
	double a1 = sqrt(nA1 * nA1) / 2;

	double lambda0 = a0 / a;
	double lambda1 = a1 / a;
	
	lambda0 = sqrt(lambda0 * lambda0);
	lambda1 = sqrt(lambda1 * lambda1);
	double lambda2 = 1.0 - lambda0 - lambda1;

	QColor c;
	c.setRed(lambda0 * c1.red() + lambda1 * c2.red() + lambda2 * c3.red());
	c.setBlue(lambda0 * c1.blue() + lambda1 * c2.blue() + lambda2 * c3.blue());
	c.setGreen(lambda0 * c1.green() + lambda1 * c2.green() + lambda2 * c3.green());

	return c;
}
QColor ViewerWidget::interpolationPixel(QString interpolation, QVector<QPointF> points, QPointF p, int z, QColor c1, QColor c2, QColor c3)
{
	if (interpolation == "None")
	{
		return QColor(255, 0, 0);
	}
	if (interpolation == "Nearest Neighbor")
	{
		return nearestNeighbor(points, p, z, c1, c2, c3);
	}
	if(interpolation == "Barycentrick")
	{
		return Barycentric(points, p, z, c1, c2, c3);
	}
}

void ViewerWidget::draw(QVector<QPointF> points, int z, QColor color, QString algorithm, QString interpolation, bool fillOn)
{
	if (points.size() == 2)
	{
		if (algorithm == "DDA")
		{
			QVector<QPointF> pointsNew = cyrusBeck(points[0], points[1]);
			if (pointsNew.size() == 2)
			{
				drawLineDDA(pointsNew[0], pointsNew[1], color, z);
			}
		}
		if (algorithm == "Bresenhamov")
		{
			QVector<QPointF> pointsNew = cyrusBeck(points[0], points[1]);
			if (pointsNew.size() == 2)
			{
				drawLineBresen(pointsNew[0], pointsNew[1], color, z);
			}
		}
	}
	else
	{
		QVector<QPointF> W = sutherlandHodgman(points, 0);

		for (int i = 0; i < W.size(); i++)
		{
			W[i] = QPointF(W[i].y(), -W[i].x());
		}

		W = sutherlandHodgman(W, 0);

		for (int i = 0; i < W.size(); i++)
		{
			W[i] = QPointF(W[i].y(), -W[i].x());
		}

		W = sutherlandHodgman(W, -img->width() + 1);

		for (int i = 0; i < W.size(); i++)
		{
			W[i] = QPointF(W[i].y(), -W[i].x());
		}

		W = sutherlandHodgman(W, -img->height() + 1);

		for (int i = 0; i < W.size(); i++)
		{
			W[i] = QPointF(W[i].y(), -W[i].x());
		}

		for (int i = 0; i < W.size() - 1; i++)
		{
			if (algorithm == "DDA")
			{
				drawLineDDA(W[i], W[i + 1], color, z);
				drawLineDDA(W.first(), W.last(), color, z);
			}
			if (algorithm == "Bresenhamov")
			{
				drawLineBresen(W[i], W[i + 1], color, z);
				drawLineBresen(W.first(), W.last(), color, z);
			}
		}

		if (fillOn)
		{
			if (W.size() == 3)
			{
				scanLineTriangle(W, z, color, interpolation);
			}
			else
			{
				if (!W.isEmpty())
				{
					scanLine(W, z, color);
				}
			}
		}
		
	}
	//update();
	drawBuffer();
}
void ViewerWidget::drawCircle(QVector<QPointF> points, int z, QColor color, QString algorithm, bool fillOn)
{
	if (algorithm == "DDA")
	{
		drawCircleDDA(points[0], points[1], color, z);
	}
	if (algorithm == "Bresenhamov")
	{
		drawCircleBresen(points[0], points[1], color, z);
	}

	if (fillOn)
	{
		scanLine(points, z, color);
	}
	//update();
	drawBuffer();
}
void ViewerWidget::drawPoints(QVector<QPointF> points, int z)
{
	QColor color = QColor("red");
	for (int i = 0; i < points.size(); i++)
	{
		setPixelZ(points[i].x(), points[i].y(), z, color);
	}
}
void ViewerWidget::drawBezierCurve(QVector<QPointF> points, int z, QColor color)
{
	if (points.size() < 2) { return; }
	else
	{
		int n = points.size();

		QVector<QVector<QPointF>> polynoms(n); //Bernsteinove bazove polynomy
		QPointF q0, q1, p;
		QPointF a, b; double qx, qy, px, py;

		//qDebug() << points;

		for (int i = 0; i < n; i++)
		{
			polynoms[0].append(points[i]);
		}

		double deltaT = 0.0001; double t = deltaT;
		q0.setX(points[0].x()); q0.setY(points[0].y());

		while (t < 1)
		{
			for (int i = 1; i < n; i++)
			{
				for (int j = 0; j < n - i; j++)
				{
					px = (1.0 - t) * polynoms[i - 1][j].x() + t * polynoms[i - 1][j + 1].x();
					py = (1.0 - t) * polynoms[i - 1][j].y() + t * polynoms[i - 1][j + 1].y();
					p.setX(px); p.setY(py);
					polynoms[i].append(p);
				}
			}

			q1.setX(polynoms[n - 1][0].x()); q1.setY(polynoms[n - 1][0].y());
			a.setX(std::floor(q0.x())); a.setY(std::floor(q0.y())); b.setX(std::floor(q1.x())); b.setY(std::floor(q1.y()));
			drawLineDDA(a, b, color, z);
			q0.setX(q1.x()); q0.setY(q1.y());
			polynoms.clear();
			polynoms.resize(n);
			for (int i = 0; i < n; i++)
			{
				polynoms[0].append(points[i]);
			}
			t += deltaT;
		}
		a.setX(q0.x()); a.setY(q0.y());
		drawLineDDA(a, points[n - 1], color, z);
	}
	drawPoints(points, z);
	//update();
	drawBuffer();
}
void ViewerWidget::clear(QColor color)
{
	for (size_t x = 0; x < img->width(); x++)
	{
		for (size_t y = 0; y < img->height(); y++)
		{
			setPixel(x, y, color);
		}
	}
	update();
}

//zBuffer
float ViewerWidget::interpolationZ(QVector<QPointF> points, QPointF p, QVector<float> zCoordinates)
{
	points = sortByYThenByX(points);

	QPointF u = QPointF(points[1].x() - points[0].x(), points[1].y() - points[0].y());
	QPointF v = QPointF(points[2].x() - points[0].x(), points[2].y() - points[0].y());
	double nA = u.x() * v.y() - u.y() * v.x();
	double a = sqrt(nA * nA) / 2;

	QPointF u0 = QPointF(points[1].x() - p.x(), points[1].y() - p.y());
	QPointF v0 = QPointF(points[2].x() - p.x(), points[2].y() - p.y());
	double nA0 = u0.x() * v0.y() - u0.y() * v0.x();
	double a0 = sqrt(nA0 * nA0) / 2;

	QPointF u1 = QPointF(points[0].x() - p.x(), points[0].y() - p.y());
	QPointF v1 = QPointF(points[2].x() - p.x(), points[2].y() - p.y());
	double nA1 = u1.x() * v1.y() - u1.y() * v1.x();
	double a1 = sqrt(nA1 * nA1) / 2;

	double lambda0 = a0 / a;
	double lambda1 = a1 / a;

	lambda0 = sqrt(lambda0 * lambda0);
	lambda1 = sqrt(lambda1 * lambda1);
	double lambda2 = 1.0 - lambda0 - lambda1;

	float z = lambda0 * zCoordinates[0] + lambda1 * zCoordinates[1] + lambda2 * zCoordinates[2];
	return z;
}
void ViewerWidget::drawBuffer()
{

	for (int i = 0; i < img->width(); i++)
	{
		for (int j = 0; j < img->height(); j++)
		{
			setPixel(i, j, fBuffer[i][j]);
		}
	}
	update();
}
void ViewerWidget::setPixelZ(int x, int y, int z, QColor color)
{
	if (isInside(x, y)) 
	{
		fBuffer[x][y] = color;
	}
}
void ViewerWidget::deleteBuffers()
{
	if (zBuffer == nullptr || fBuffer == nullptr) {
		return;
	}

	for (int i = 0; i < img->width(); i++)
	{
		delete zBuffer[i];
	}
	delete zBuffer;
	zBuffer = nullptr;

	for (int i = 0; i < img->width(); i++)
	{
		delete fBuffer[i];
	}
	delete fBuffer;
	fBuffer = nullptr;
}
void ViewerWidget::clearBuffers()
{
	for (int i = 0; i < img->width(); i++)
	{
		for (int j = 0; j < img->height(); j++)
		{
			zBuffer[i][j] = std::numeric_limits<int>::min();
		}
	}
	for (int i = 0; i < img->width(); i++)
	{
		for (int j = 0; j < img->height(); j++)
		{
			fBuffer[i][j] = QColor(255, 255, 255);
		}
	}
}
void ViewerWidget::createBuffers()
{
	if (zBuffer == nullptr)
	{
		zBuffer = new int* [img->width()];
		for (int i = 0; i < img->width(); i++)
		{
			zBuffer[i] = new int[img->height()];
		}
		for (int i = 0; i < img->width(); i++)
		{
			for (int j = 0; j < img->height(); j++)
			{
				zBuffer[i][j] = std::numeric_limits<int>::min();
			}
		}
	}

	if (fBuffer == nullptr)
	{
		fBuffer = new QColor * [img->width()];
		for (int i = 0; i < img->width(); i++)
		{
			fBuffer[i] = new QColor[img->height()];
		}
		for (int i = 0; i < img->width(); i++)
		{
			for (int j = 0; j < img->height(); j++)
			{
				fBuffer[i][j] = QColor(255, 255, 255);
			}
		}
	}
}
/*void ViewerWidget::scanLineBuffer(QVector<QPointF> points, QVector<float> zCoordinates, int z, QColor c1, QColor c2, QColor c3)
{
	points = sortByYThenByX(points);

	QVector<Edge> edges(4);
	Edge a, b, c, d;
	QPointF p; // priesecnik

	if ((points[0].y() == points[1].y() && points[1].y() == points[2].y()) ||
		(points[0].x() == points[1].x() && points[1].x() == points[2].x()))
	{
		return;
	}
	if (points[0].y() == points[1].y())
	{
		//spodny troj
		a = Edge(points[0], points[2]);
		b = Edge(points[1], points[2]);

	}
	else if (points[1].y() == points[2].y())
	{
		//horny troj
		a = Edge(points[0], points[1]);
		b = Edge(points[0], points[2]);
	}
	else
	{
		double dy = points[2].y() - points[0].y();
		double dx = points[2].x() - points[0].x();
		double m = dy / dx;
		double w;
		if (m == 0) { w = 0; }
		else { w = 1.0 / m; }
		double x = (points[1].y() - points[0].y()) * w + points[0].x();
		p.setX(x);
		p.setY(points[1].y());

		if (points[1].x() > p.x())
		{
			a = Edge(points[0], p);
			b = Edge(points[0], points[1]);

			c = Edge(p, points[2]);
			d = Edge(points[1], points[2]);
		}
		else
		{
			a = Edge(points[0], points[1]);
			b = Edge(points[0], p);

			c = Edge(points[1], points[2]);
			d = Edge(p, points[2]);
		}
	}

	double y = a.getYZ();
	double yMax = b.getYK();
	double x1 = a.getXZ();
	double x2 = b.getXZ();

	while (y < yMax)
	{
		if (x1 != x2)
		{
			for (int i = x1; i < x2; i++)
			{
				QPointF t = QPointF(i, y);
				QColor color = interpolationPixel("Barycentrick", points, t, z, c1, c2, c3);

				if (zBuffer[i][(int)y] < z)
				{
					zBuffer[i][(int)y] = z;
					fBuffer[i][(int)y] = color;
				}
			}
		}
		x1 += a.getW();
		x2 += b.getW();
		y++;
	}

	if (!p.isNull())
	{
		y = c.getYZ();
		yMax = c.getYK();
		x1 = c.getXZ();
		x2 = d.getXZ();

		while (y <= yMax)
		{
			for (int i = x1; i <= x2; i++)
			{
				QPointF t = QPointF(i, y);
				QColor color = interpolationPixel("Barycentrick", points, t, z, c1, c2, c3);

				if (zBuffer[i][(int)y] < z)
				{
					zBuffer[i][(int)y] = z;
					fBuffer[i][(int)y] = color;
				}
			}
			x1 += c.getW();
			x2 += d.getW();
			y++;
		}
	}
}*/

//Slots
void ViewerWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QRect area = event->rect();
	painter.drawImage(area, *img, area);
}

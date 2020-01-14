/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     kirigaya <kirigaya@mkacg.com>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "borderwidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>

BorderWidget::BorderWidget(QWidget *parent)
    : DFrame(parent)
    , m_checked(false)
{
    setLineWidth(0);
}

void BorderWidget::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
    m_size = m_pixmap.size();

    update();
}

void BorderWidget::setChecked(bool checked)
{
    m_checked = checked;

    update();
}

void BorderWidget::updateInterface(float f)
{
    m_size = m_pixmap.size() * f;
    update();
}

void BorderWidget::paintEvent(QPaintEvent *event)
{
    DFrame::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect pixRect(QPoint(6, 6), (m_size - QSize(3,3)) / devicePixelRatioF());
    pixRect.moveCenter(rect().center());

    // draw background
    QPainterPath contentPath;
    contentPath.addRoundedRect(pixRect, 10, 10);
    painter.setClipPath(contentPath);
    painter.drawPixmap(pixRect, m_pixmap);

    if (!m_checked) {
        QPen pen(QColor(0, 0, 0, 0.2 * 255));
        pen.setWidth(1);
        painter.setPen(pen);
        QPainterPath Frame;
        QRect frameRect = pixRect;
        frameRect.setHeight(frameRect.height() + 6);
        frameRect.moveCenter(rect().center());
        Frame.addRoundedRect(frameRect, 10, 10);
        painter.setClipPath(Frame);
        painter.drawPath(Frame);
    }

    // draw border
    QPainterPath path;
    path.addRoundedRect(rect().adjusted(2, 2, -3, -3), 10, 10);
    painter.setClipRect(QRect(), Qt::NoClip);
    if (m_checked) {
        QPen pen(QColor("#0081FF"));
        pen.setWidth(4);

        painter.setPen(pen);
        painter.drawPath(path);
    }
}

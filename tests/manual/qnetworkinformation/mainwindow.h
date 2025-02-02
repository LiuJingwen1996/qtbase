/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qlabel.h>
#include <QtCore/qmetaobject.h>

#include <QtNetwork/qnetworkinformation.h>

template<typename QEnum>
QString enumToString(const QEnum value)
{
    return QString::fromUtf8(QMetaEnum::fromType<QEnum>().valueToKey(int(value)));
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    using Reachability = QNetworkInformation::Reachability;
    using TransportMedium = QNetworkInformation::TransportMedium;

public:
    MainWindow() : QMainWindow(nullptr)
    {
        label->setText("hello");
        setCentralWidget(label);
    }

public slots:
    void updateReachability(Reachability newValue)
    {
        reachability = newValue;
        updateText();
    }

    void updateCaptiveState(bool newValue)
    {
        captive = newValue;
        updateText();
    }

    void updateTransportMedium(TransportMedium newValue)
    {
        transportMedium = newValue;
        updateText();
    }

private:
    void updateText()
    {
        QString str =
                QLatin1String("Reachability: %1\nBehind captive portal: %2\nTransport medium: %3")
                        .arg(enumToString(reachability), QStringView(captive ? u"true" : u"false"),
                             enumToString(transportMedium));
        label->setText(str);
    }

    QLabel *const label = new QLabel(this);
    Reachability reachability = Reachability::Unknown;
    TransportMedium transportMedium = TransportMedium::Unknown;
    bool captive = false;
};

#endif

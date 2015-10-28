/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtSerialBus module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QMODBUSTCPCLIENT_H
#define QMODBUSTCPCLIENT_H

#include <QtSerialBus/qmodbusclient.h>
#include <QtSerialBus/qmodbusdataunit.h>
#include <QtSerialBus/qmodbusreply.h>

QT_BEGIN_NAMESPACE

class QModbusTcpClientPrivate;

class Q_SERIALBUS_EXPORT QModbusTcpClient : public QModbusClient
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QModbusTcpClient)

public:
    explicit QModbusTcpClient(QObject *parent = Q_NULLPTR);
    ~QModbusTcpClient();

    virtual QModbusReply *sendReadRequest(const QModbusDataUnit &read,
                                          int slaveAddress) Q_DECL_OVERRIDE;
    virtual QModbusReply *sendWriteRequest(const QModbusDataUnit &write,
                                           int slaveAddress) Q_DECL_OVERRIDE;
    virtual QModbusReply *sendReadWriteRequest(const QModbusDataUnit &read,
                                   const QModbusDataUnit &write, int slaveAddress) Q_DECL_OVERRIDE;

protected:
    QModbusTcpClient(QModbusTcpClientPrivate &dd, QObject *parent = Q_NULLPTR);

    void close() Q_DECL_OVERRIDE { /* TODO: Implement! */ }
    bool open() Q_DECL_OVERRIDE { /* TODO: Implement! */ return false; }
};

QT_END_NAMESPACE

#endif // QMODBUSTCPCLIENT_H

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

#ifndef QMODBUSDEVICE_P_H
#define QMODBUSDEVICE_P_H

#include "qmodbusdevice.h"
#include "QtCore/private/qobject_p.h"

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API. It exists purely as an
// implementation detail. This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

QT_BEGIN_NAMESPACE

class QModbusDevicePrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QModbusDevice)
public:
    QModbusDevicePrivate()
        : state(QModbusDevice::UnconnectedState),
          error(QModbusDevice::NoError)
    {
    }

    quint8 calculateLRC(const char *data, qint32 len) const
    {
        quint32 lrc = 0;
        while (len--)
            lrc += *data++;
        return -(quint8(lrc));
    }
    bool checkLRC(const char *data, qint32 len, quint8 lrc) const
    {
        return calculateLRC(data, len) == lrc;
    }

    quint16 calculateCRC(const char *data, qint32 len) const
    {
        // Generated by pycrc v0.8.3, https://pycrc.org
        // Width = 16, Poly = 0x8005, XorIn = 0xffff, ReflectIn = True,
        // XorOut = 0x0000, ReflectOut = True, Algorithm = bit-by-bit-fast

        quint16 crc = 0xFFFF;
        while (len--) {
            const quint8 c = *data++;
            for (qint32 i = 0x01; i & 0xFF; i <<= 1) {
                bool bit = crc & 0x8000;
                if (c & i)
                    bit = !bit;
                crc <<= 1;
                if (bit)
                    crc ^= 0x8005;
            }
            crc &= 0xFFFF;
        }
        crc = crc_reflect(crc & 0xFFFF, 16) ^ 0x0000;
        return (crc >> 8) | (crc << 8); // swap bytes
    }
    bool checkCRC(const char *data, qint32 len, quint16 crc) const
    {
        return calculateCRC(data, len) == crc;
    }

    QModbusDevice::ModBusDeviceState state;
    QModbusDevice::ModBusError error;
    QString errorString;
    QString portName;

private:
    quint16 crc_reflect(quint16 data, qint32 len) const
    {
        // Generated by pycrc v0.8.3, https://pycrc.org
        // Width = 16, Poly = 0x8005, XorIn = 0xffff, ReflectIn = True,
        // XorOut = 0x0000, ReflectOut = True, Algorithm = bit-by-bit-fast

        quint16 ret = data & 0x01;
        for (qint32 i = 1; i < len; i++) {
            data >>= 1;
            ret = (ret << 1) | (data & 0x01);
        }
        return ret;
    }
};

QT_END_NAMESPACE

#endif // QMODBUSDEVICE_P_H

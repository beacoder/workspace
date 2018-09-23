#!/usr/bin/python
# -*- coding: utf-8 -*-
#
# Copyright 2018-2018 humingchen
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may
# not use this file except in compliance with the License. You may obtain
# a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations
# under the License.

from __future__ import absolute_import, division, print_function, \
    with_statement

import sys
import os
import logging
import signal
import socket
import struct
import messagetransceiver


BUF_SIZE = 65536


class UDPClient(messagetransceiver.IMessageSender):
    """Transmitting incomming/outgoing messages."""

    def __init__(self, server_addr, server_port):
        self._server_addr = server_addr
        self._server_port = server_port
        self._sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._sock.setblocking(False)

    def get_client_sock(self):
        return self._sock

    def close(self):
        self._sock.close()

    def set_msg_recver(self, msg_recver):
        self._recver = msg_recver

    def send_message(self, msg, to_addr):
        data = struct.pack(">H", msg.MSG_TYPE) + msg.to_bytes();
        print('Sent message {msg} to {peer}.'.format(msg=data, peer=to_addr))
        self._sock.sendto(data, to_addr)

    def _on_recv_data(self):
        data, addr = self._sock.recvfrom(BUF_SIZE)
        if not data:
            logging.debug('UDP on_recv_data: data is empty')
            return
        print('Got message {msg} from {peer}.'.format(msg=data, peer=addr))
        print('')
        (msg_type,), msg_body = struct.unpack(">H", data[:2]), data[2:]
        message = create_message(msg_type, msg_body)
        if self._recver is not None:
            self._recver(message, addr)

    def handle_event(self, sock, fd, event):
        if sock == self._sock:
            if event & eventloop.POLL_ERR:
                logging.error('UDP client_socket err')
            self._on_recv_data()
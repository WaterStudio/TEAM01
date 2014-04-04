(function () {
    var isArray = Array.isArray;

    var root = this;

    function EventEmitter() {
    }


    if (typeof module !== 'undefined' && module.exports) {
        module.exports.EventEmitter = EventEmitter;
    }
    else {
        root = window;
        root.EventEmitter = EventEmitter;
    }

    // By default EventEmitters will print a warning if more than
    // 10 listeners are added to it. This is a useful default which
    // helps finding memory leaks.
    //
    // Obviously not all Emitters should be limited to 10. This function allows
    // that to be increased. Set to zero for unlimited.
    var defaultMaxListeners = 10;
    EventEmitter.prototype.setMaxListeners = function (n) {
        if (!this._events) this._events = {};
        this._maxListeners = n;
    };


    EventEmitter.prototype.emit = function () {
        var type = arguments[0];
        // If there is no 'error' event listener then throw.
        if (type === 'error') {
            if (!this._events || !this._events.error ||
                (isArray(this._events.error) && !this._events.error.length)) {
                if (this.domain) {
                    var er = arguments[1];
                    er.domain_emitter = this;
                    er.domain = this.domain;
                    er.domain_thrown = false;
                    this.domain.emit('error', er);
                    return false;
                }

                if (arguments[1] instanceof Error) {
                    throw arguments[1]; // Unhandled 'error' event
                } else {
                    throw new Error("Uncaught, unspecified 'error' event.");
                }
                return false;
            }
        }

        if (!this._events) return false;
        var handler = this._events[type];
        if (!handler) return false;

        if (typeof handler == 'function') {
            if (this.domain) {
                this.domain.enter();
            }
            switch (arguments.length) {
                // fast cases
                case 1:
                    handler.call(this);
                    break;
                case 2:
                    handler.call(this, arguments[1]);
                    break;
                case 3:
                    handler.call(this, arguments[1], arguments[2]);
                    break;
                // slower
                default:
                    var l = arguments.length;
                    var args = new Array(l - 1);
                    for (var i = 1; i < l; i++) args[i - 1] = arguments[i];
                    handler.apply(this, args);
            }
            if (this.domain) {
                this.domain.exit();
            }
            return true;

        } else if (isArray(handler)) {
            if (this.domain) {
                this.domain.enter();
            }
            var l = arguments.length;
            var args = new Array(l - 1);
            for (var i = 1; i < l; i++) args[i - 1] = arguments[i];

            var listeners = handler.slice();
            for (var i = 0, l = listeners.length; i < l; i++) {
                listeners[i].apply(this, args);
            }
            if (this.domain) {
                this.domain.exit();
            }
            return true;

        } else {
            return false;
        }
    };

    EventEmitter.prototype.addListener = function (type, listener) {
        if ('function' !== typeof listener) {
            throw new Error('addListener only takes instances of Function');
        }

        if (!this._events) this._events = {};

        // To avoid recursion in the case that type == "newListeners"! Before
        // adding it to the listeners, first emit "newListeners".
        this.emit('newListener', type, typeof listener.listener === 'function' ?
            listener.listener : listener);

        if (!this._events[type]) {
            // Optimize the case of one listener. Don't need the extra array object.
            this._events[type] = listener;
        } else if (isArray(this._events[type])) {

            // If we've already got an array, just append.
            this._events[type].push(listener);

        } else {
            // Adding the second element, need to change to array.
            this._events[type] = [this._events[type], listener];

        }

        // Check for listener leak
        if (isArray(this._events[type]) && !this._events[type].warned) {
            var m;
            if (this._maxListeners !== undefined) {
                m = this._maxListeners;
            } else {
                m = defaultMaxListeners;
            }

            if (m && m > 0 && this._events[type].length > m) {
                this._events[type].warned = true;
                console.error('(node) warning: possible EventEmitter memory ' +
                        'leak detected. %d listeners added. ' +
                        'Use emitter.setMaxListeners() to increase limit.',
                    this._events[type].length);
                console.trace();
            }
        }

        return this;
    };

    EventEmitter.prototype.on = EventEmitter.prototype.addListener;

    EventEmitter.prototype.once = function (type, listener) {
        if ('function' !== typeof listener) {
            throw new Error('.once only takes instances of Function');
        }

        var self = this;

        function g() {
            self.removeListener(type, g);
            listener.apply(this, arguments);
        };

        g.listener = listener;
        self.on(type, g);

        return this;
    };

    EventEmitter.prototype.removeListener = function (type, listener) {
        if ('function' !== typeof listener) {
            throw new Error('removeListener only takes instances of Function');
        }

        // does not use listeners(), so no side effect of creating _events[type]
        if (!this._events || !this._events[type]) return this;

        var list = this._events[type];

        if (isArray(list)) {
            var position = -1;
            for (var i = 0, length = list.length; i < length; i++) {
                if (list[i] === listener ||
                    (list[i].listener && list[i].listener === listener)) {
                    position = i;
                    break;
                }
            }

            if (position < 0) return this;
            list.splice(position, 1);
        } else if (list === listener ||
            (list.listener && list.listener === listener)) {
            delete this._events[type];
        }

        return this;
    };

    EventEmitter.prototype.removeAllListeners = function (type) {
        if (arguments.length === 0) {
            this._events = {};
            return this;
        }

        var events = this._events && this._events[type];
        if (!events) return this;

        if (isArray(events)) {
            events.splice(0);
        } else {
            this._events[type] = null;
        }

        return this;
    };

    EventEmitter.prototype.listeners = function (type) {
        if (!this._events) this._events = {};
        if (!this._events[type]) this._events[type] = [];
        if (!isArray(this._events[type])) {
            this._events[type] = [this._events[type]];
        }
        return this._events[type];
    }
})();

(function (exports, ByteArray, global) {
    var Protocol = exports;

    var PKG_HEAD_BYTES = 4;
    var MSG_FLAG_BYTES = 1;
    var MSG_ROUTE_CODE_BYTES = 2;
    var MSG_ID_MAX_BYTES = 5;
    var MSG_ROUTE_LEN_BYTES = 1;

    var MSG_ROUTE_CODE_MAX = 0xffff;

    var MSG_COMPRESS_ROUTE_MASK = 0x1;
    var MSG_TYPE_MASK = 0x7;

    var Package = Protocol.Package = {};
    var Message = Protocol.Message = {};

    Package.TYPE_HANDSHAKE = 1;
    Package.TYPE_HANDSHAKE_ACK = 2;
    Package.TYPE_HEARTBEAT = 3;
    Package.TYPE_DATA = 4;
    Package.TYPE_KICK = 5;

    Message.TYPE_REQUEST = 0;
    Message.TYPE_NOTIFY = 1;
    Message.TYPE_RESPONSE = 2;
    Message.TYPE_PUSH = 3;

    /**
     * pomele client encode
     * id message id;
     * route message route
     * msg message body
     * socketio current support string
     */
    Protocol.strencode = function (str) {
        var byteArray = new ByteArray(str.length * 3);
        var offset = 0;
        for (var i = 0; i < str.length; i++) {
            var charCode = str.charCodeAt(i);
            var codes = null;
            if (charCode <= 0x7f) {
                codes = [charCode];
            } else if (charCode <= 0x7ff) {
                codes = [0xc0 | (charCode >> 6), 0x80 | (charCode & 0x3f)];
            } else {
                codes = [0xe0 | (charCode >> 12), 0x80 | ((charCode & 0xfc0) >> 6), 0x80 | (charCode & 0x3f)];
            }
            for (var j = 0; j < codes.length; j++) {
                byteArray[offset] = codes[j];
                ++offset;
            }
        }
        var _buffer = new ByteArray(offset);
        copyArray(_buffer, 0, byteArray, 0, offset);
        return _buffer;
    };

    /**
     * client decode
     * msg String data
     * return Message Object
     */
    Protocol.strdecode = function (buffer) {
        var bytes = new ByteArray(buffer);
        var array = [];
        var offset = 0;
        var charCode = 0;
        var end = bytes.length;
        while (offset < end) {
            if (bytes[offset] < 128) {
                charCode = bytes[offset];
                offset += 1;
            } else if (bytes[offset] < 224) {
                charCode = ((bytes[offset] & 0x3f) << 6) + (bytes[offset + 1] & 0x3f);
                offset += 2;
            } else {
                charCode = ((bytes[offset] & 0x0f) << 12) + ((bytes[offset + 1] & 0x3f) << 6) + (bytes[offset + 2] & 0x3f);
                offset += 3;
            }
            array.push(charCode);
        }
        return String.fromCharCode.apply(null, array);
    };

    /**
     * Package protocol encode.
     *
     * Pomelo package format:
     * +------+-------------+------------------+
     * | type | body length |       body       |
     * +------+-------------+------------------+
     *
     * Head: 4bytes
     *   0: package type,
     *      1 - handshake,
     *      2 - handshake ack,
     *      3 - heartbeat,
     *      4 - data
     *      5 - kick
     *   1 - 3: big-endian body length
     * Body: body length bytes
     *
     * @param  {Number}    type   package type
     * @param  {ByteArray} body   body content in bytes
     * @return {ByteArray}        new byte array that contains encode result
     */
    Package.encode = function (type, body) {
        var length = body ? body.length : 0;
        var buffer = new ByteArray(PKG_HEAD_BYTES + length);
        var index = 0;
        buffer[index++] = type & 0xff;
        buffer[index++] = (length >> 16) & 0xff;
        buffer[index++] = (length >> 8) & 0xff;
        buffer[index++] = length & 0xff;
        if (body) {
            copyArray(buffer, index, body, 0, length);
        }
        return buffer;
    };

    /**
     * Package protocol decode.
     * See encode for package format.
     *
     * @param  {ByteArray} buffer byte array containing package content
     * @return {Object}           {type: package type, buffer: body byte array}
     */
    Package.decode = function (buffer) {
        var bytes = new ByteArray(buffer);
        var type = bytes[0];
        var index = 1;
        var length = ((bytes[index++]) << 16 | (bytes[index++]) << 8 | bytes[index++]) >>> 0;
        var body = length ? new ByteArray(length) : null;
        copyArray(body, 0, bytes, PKG_HEAD_BYTES, length);
        return {'type': type, 'body': body};
    };

    /**
     * Message protocol encode.
     *
     * @param  {Number} id            message id
     * @param  {Number} type          message type
     * @param  {Number} compressRoute whether compress route
     * @param  {Number|String} route  route code or route string
     * @param  {Buffer} msg           message body bytes
     * @return {Buffer}               encode result
     */
    Message.encode = function (id, type, compressRoute, route, msg) {
        // caculate message max length
        var idBytes = msgHasId(type) ? caculateMsgIdBytes(id) : 0;
        var msgLen = MSG_FLAG_BYTES + idBytes;

        if (msgHasRoute(type)) {
            if (compressRoute) {
                if (typeof route !== 'number') {
                    throw new Error('error flag for number route!');
                }
                msgLen += MSG_ROUTE_CODE_BYTES;
            } else {
                msgLen += MSG_ROUTE_LEN_BYTES;
                if (route) {
                    route = Protocol.strencode(route);
                    if (route.length > 255) {
                        throw new Error('route maxlength is overflow');
                    }
                    msgLen += route.length;
                }
            }
        }

        if (msg) {
            msgLen += msg.length;
        }

        var buffer = new ByteArray(msgLen);
        var offset = 0;

        // add flag
        offset = encodeMsgFlag(type, compressRoute, buffer, offset);

        // add message id
        if (msgHasId(type)) {
            offset = encodeMsgId(id, idBytes, buffer, offset);
        }

        // add route
        if (msgHasRoute(type)) {
            offset = encodeMsgRoute(compressRoute, route, buffer, offset);
        }

        // add body
        if (msg) {
            offset = encodeMsgBody(msg, buffer, offset);
        }

        return buffer;
    };

    /**
     * Message protocol decode.
     *
     * @param  {Buffer|Uint8Array} buffer message bytes
     * @return {Object}            message object
     */
    Message.decode = function (buffer) {
        var bytes = new ByteArray(buffer);
        var bytesLen = bytes.length || bytes.byteLength;
        var offset = 0;
        var id = 0;
        var route = null;

        // parse flag
        var flag = bytes[offset++];
        var compressRoute = flag & MSG_COMPRESS_ROUTE_MASK;
        var type = (flag >> 1) & MSG_TYPE_MASK;

        // parse id
        if (msgHasId(type)) {
            var byte = bytes[offset++];
            id = byte & 0x7f;
            while (byte & 0x80) {
                id <<= 7;
                byte = bytes[offset++];
                id |= byte & 0x7f;
            }
        }

        // parse route
        if (msgHasRoute(type)) {
            if (compressRoute) {
                route = (bytes[offset++]) << 8 | bytes[offset++];
            } else {
                var routeLen = bytes[offset++];
                if (routeLen) {
                    route = new ByteArray(routeLen);
                    copyArray(route, 0, bytes, offset, routeLen);
                    route = Protocol.strdecode(route);
                } else {
                    route = '';
                }
                offset += routeLen;
            }
        }

        // parse body
        var bodyLen = bytesLen - offset;
        var body = new ByteArray(bodyLen);

        copyArray(body, 0, bytes, offset, bodyLen);

        return {'id': id, 'type': type, 'compressRoute': compressRoute,
            'route': route, 'body': body};
    };

    var copyArray = function (dest, doffset, src, soffset, length) {
        if ('function' === typeof src.copy) {
            // Buffer
            src.copy(dest, doffset, soffset, soffset + length);
        } else {
            // Uint8Array
            for (var index = 0; index < length; index++) {
                dest[doffset++] = src[soffset++];
            }
        }
    };

    var msgHasId = function (type) {
        return type === Message.TYPE_REQUEST || type === Message.TYPE_RESPONSE;
    };

    var msgHasRoute = function (type) {
        return type === Message.TYPE_REQUEST || type === Message.TYPE_NOTIFY ||
            type === Message.TYPE_PUSH;
    };

    var caculateMsgIdBytes = function (id) {
        var len = 0;
        do {
            len += 1;
            id >>= 7;
        } while (id > 0);
        return len;
    };

    var encodeMsgFlag = function (type, compressRoute, buffer, offset) {
        if (type !== Message.TYPE_REQUEST && type !== Message.TYPE_NOTIFY &&
            type !== Message.TYPE_RESPONSE && type !== Message.TYPE_PUSH) {
            throw new Error('unkonw message type: ' + type);
        }

        buffer[offset] = (type << 1) | (compressRoute ? 1 : 0);

        return offset + MSG_FLAG_BYTES;
    };

    var encodeMsgId = function (id, idBytes, buffer, offset) {
        var index = offset + idBytes - 1;
        buffer[index--] = id & 0x7f;
        while (index >= offset) {
            id >>= 7;
            buffer[index--] = id & 0x7f | 0x80;
        }
        return offset + idBytes;
    };

    var encodeMsgRoute = function (compressRoute, route, buffer, offset) {
        if (compressRoute) {
            if (route > MSG_ROUTE_CODE_MAX) {
                throw new Error('route number is overflow');
            }

            buffer[offset++] = (route >> 8) & 0xff;
            buffer[offset++] = route & 0xff;
        } else {
            if (route) {
                buffer[offset++] = route.length & 0xff;
                copyArray(buffer, offset, route, 0, route.length);
                offset += route.length;
            } else {
                buffer[offset++] = 0;
            }
        }

        return offset;
    };

    var encodeMsgBody = function (msg, buffer, offset) {
        copyArray(buffer, offset, msg, 0, msg.length);
        return offset + msg.length;
    };

})('object' === typeof module ? module.exports : (this.Protocol = {}), 'object' === typeof module ? Buffer : Uint8Array, this);

(function () {
    var JS_WS_CLIENT_TYPE = 'js-websocket';
    var JS_WS_CLIENT_VERSION = '0.0.1';

    var Protocol = window.Protocol;
    var Package = Protocol.Package;
    var Message = Protocol.Message;
    var EventEmitter = window.EventEmitter;

    var RES_OK = 200;
    var RES_FAIL = 500;
    var RES_OLD_CLIENT = 501;

    if (typeof Object.create !== 'function') {
        Object.create = function (o) {
            function F() {
            }

            F.prototype = o;
            return new F();
        };
    }

    var root = window;
    var pomelo = Object.create(EventEmitter.prototype); // object extend from object
    root.pomelo = pomelo;
    var socket = null;
    var reqId = 0;
    var callbacks = {};
    var handlers = {};
    //Map from request id to route
    var routeMap = {};

    var heartbeatInterval = 0;
    var heartbeatTimeout = 0;
    var nextHeartbeatTimeout = 0;
    var gapThreshold = 100;   // heartbeat gap threashold
    var heartbeatId = null;
    var heartbeatTimeoutId = null;

    var handshakeCallback = null;

    var handshakeBuffer = {
        'sys': {
            type: JS_WS_CLIENT_TYPE,
            version: JS_WS_CLIENT_VERSION
        },
        'user': {
        }
    };

    var initCallback = null;

    pomelo.init = function (params, cb) {
        initCallback = cb;
        var host = params.host;
        var port = params.port;

        var url = 'ws://' + host;
        if (port) {
            url += ':' + port;
        }

        handshakeBuffer.user = params.user;
        handshakeCallback = params.handshakeCallback;
        initWebSocket(url, cb);
    };

    var initWebSocket = function (url, cb) {
        console.log('connect to ' + url);
        var onopen = function (event) {
            var obj = Package.encode(Package.TYPE_HANDSHAKE, Protocol.strencode(JSON.stringify(handshakeBuffer)));
            send(obj);
        };
        var onmessage = function (event) {
            processPackage(Package.decode(event.data), cb);
            // new package arrived, update the heartbeat timeout
            if (heartbeatTimeout) {
                nextHeartbeatTimeout = Date.now() + heartbeatTimeout;
            }
        };
        var onerror = function (event) {
            pomelo.emit('io-error', event);
            console.error('socket error: ', event);
        };
        var onclose = function (event) {
            pomelo.emit('close', event);
            console.error('socket close: ', event);
        };
        socket = new WebSocket(url);
        socket.binaryType = 'arraybuffer';
        socket.onopen = onopen;
        socket.onmessage = onmessage;
        socket.onerror = onerror;
        socket.onclose = onclose;
    };

    pomelo.disconnect = function () {
        if (socket) {
            if (socket.disconnect) socket.disconnect();
            if (socket.close) socket.close();
            console.log('disconnect');
            socket = null;
        }

        if (heartbeatId) {
            clearTimeout(heartbeatId);
            heartbeatId = null;
        }
        if (heartbeatTimeoutId) {
            clearTimeout(heartbeatTimeoutId);
            heartbeatTimeoutId = null;
        }
    };

    pomelo.request = function (route, msg, cb) {
        if (arguments.length === 2 && typeof msg === 'function') {
            cb = msg;
            msg = {};
        } else {
            msg = msg || {};
        }
        route = route || msg.route;
        if (!route) {
            return;
        }

        reqId++;
        sendMessage(reqId, route, msg);

        callbacks[reqId] = cb;
        routeMap[reqId] = route;
    };

    pomelo.notify = function (route, msg) {
        msg = msg || {};
        sendMessage(0, route, msg);
    };

    var sendMessage = function (reqId, route, msg) {
        var type = reqId ? Message.TYPE_REQUEST : Message.TYPE_NOTIFY;

        //compress message by protobuf
        var protos = !!pomelo.data.protos ? pomelo.data.protos.client : {};
        if (!!protos[route]) {
            msg = protobuf.encode(route, msg);
        } else {
            msg = Protocol.strencode(JSON.stringify(msg));
        }


        var compressRoute = 0;
        if (pomelo.dict && pomelo.dict[route]) {
            route = pomelo.dict[route];
            compressRoute = 1;
        }

        msg = Message.encode(reqId, type, compressRoute, route, msg);
        var packet = Package.encode(Package.TYPE_DATA, msg);
        send(packet);
    };

    var send = function (packet) {
        socket.send(packet.buffer);
    };


    var handler = {};

    var heartbeat = function (data) {
        if (!heartbeatInterval) {
            // no heartbeat
            return;
        }

        var obj = Package.encode(Package.TYPE_HEARTBEAT);
        if (heartbeatTimeoutId) {
            clearTimeout(heartbeatTimeoutId);
            heartbeatTimeoutId = null;
        }

        if (heartbeatId) {
            // already in a heartbeat interval
            return;
        }

        heartbeatId = setTimeout(function () {
            heartbeatId = null;
            send(obj);

            nextHeartbeatTimeout = Date.now() + heartbeatTimeout;
            heartbeatTimeoutId = setTimeout(heartbeatTimeoutCb, heartbeatTimeout);
        }, heartbeatInterval);
    };

    var heartbeatTimeoutCb = function () {
        var gap = nextHeartbeatTimeout - Date.now();
        if (gap > gapThreshold) {
            heartbeatTimeoutId = setTimeout(heartbeatTimeoutCb, gap);
        } else {
            console.error('server heartbeat timeout');
            pomelo.emit('heartbeat timeout');
            pomelo.disconnect();
        }
    };

    var handshake = function (data) {
        data = JSON.parse(Protocol.strdecode(data));
        if (data.code === RES_OLD_CLIENT) {
            pomelo.emit('error', 'client version not fullfill');
            return;
        }

        if (data.code !== RES_OK) {
            pomelo.emit('error', 'handshake fail');
            return;
        }

        handshakeInit(data);

        var obj = Package.encode(Package.TYPE_HANDSHAKE_ACK);
        send(obj);
        if (initCallback) {
            initCallback(socket);
            initCallback = null;
        }
    };

    var onData = function (data) {
        //probuff decode
        var msg = Message.decode(data);

        if (msg.id > 0) {
            msg.route = routeMap[msg.id];
            delete routeMap[msg.id];
            if (!msg.route) {
                return;
            }
        }

        msg.body = deCompose(msg);

        processMessage(pomelo, msg);
    };

    var onKick = function (data) {
        pomelo.emit('onKick');
    };

    handlers[Package.TYPE_HANDSHAKE] = handshake;
    handlers[Package.TYPE_HEARTBEAT] = heartbeat;
    handlers[Package.TYPE_DATA] = onData;
    handlers[Package.TYPE_KICK] = onKick;

    var processPackage = function (msg) {
        handlers[msg.type](msg.body);
    };

    var processMessage = function (pomelo, msg) {
        if (!msg.id) {
            // server push message
            pomelo.emit(msg.route, msg.body);
            return;
        }

        //if have a id then find the callback function with the request
        var cb = callbacks[msg.id];

        delete callbacks[msg.id];
        if (typeof cb !== 'function') {
            return;
        }

        cb(msg.body);
        return;
    };

    var processMessageBatch = function (pomelo, msgs) {
        for (var i = 0, l = msgs.length; i < l; i++) {
            processMessage(pomelo, msgs[i]);
        }
    };

    var deCompose = function (msg) {
        var protos = !!pomelo.data.protos ? pomelo.data.protos.server : {};
        var abbrs = pomelo.data.abbrs;
        var route = msg.route;

        //Decompose route from dict
        if (msg.compressRoute) {
            if (!abbrs[route]) {
                return {};
            }

            route = msg.route = abbrs[route];
        }
        if (!!protos[route]) {
            return protobuf.decode(route, msg.body);
        } else {
            return JSON.parse(Protocol.strdecode(msg.body));
        }

        return msg;
    };

    var handshakeInit = function (data) {
        if (data.sys && data.sys.heartbeat) {
            heartbeatInterval = data.sys.heartbeat * 1000;   // heartbeat interval
            heartbeatTimeout = heartbeatInterval * 2;        // max heartbeat timeout
        } else {
            heartbeatInterval = 0;
            heartbeatTimeout = 0;
        }

        initData(data);

        if (typeof handshakeCallback === 'function') {
            handshakeCallback(data.user);
        }
    };

    //Initilize data used in pomelo client
    var initData = function (data) {
        if (!data || !data.sys) {
            return;
        }
        pomelo.data = pomelo.data || {};
        var dict = data.sys.dict;
        var protos = data.sys.protos;

        //Init compress dict
        if (dict) {
            pomelo.data.dict = dict;
            pomelo.data.abbrs = {};

            for (var route in dict) {
                pomelo.data.abbrs[dict[route]] = route;
            }
        }

        //Init protobuf protos
        if (protos) {
            pomelo.data.protos = {
                server: protos.server || {},
                client: protos.client || {}
            };
            if (!!protobuf) {
                protobuf.init({encoderProtos: protos.client, decoderProtos: protos.server});
            }
        }
    };
})();

(function (exports, global) {
    var MsgDecoder = exports;

    var codec = protobuf.codec;
    var util = protobuf.util;

    var buffer;
    var offset = 0;

    MsgDecoder.init = function (protos) {
        this.protos = protos || {};
    };

    MsgDecoder.setProtos = function (protos) {
        if (!!protos) {
            this.protos = protos;
        }
    };

    MsgDecoder.decode = function (route, buf) {
        var protos = this.protos[route];

        buffer = buf;
        offset = 0;

        if (!!protos) {
            return decodeMsg({}, protos, buffer.length);
        }

        return null;
    };

    function decodeMsg(msg, protos, length) {
        while (offset < length) {
            var head = getHead();
            var type = head.type;
            var tag = head.tag;
            var name = protos.__tags[tag];

            switch (protos[name].option) {
                case 'optional' :
                case 'required' :
                    msg[name] = decodeProp(protos[name].type, protos);
                    break;
                case 'repeated' :
                    if (!msg[name]) {
                        msg[name] = [];
                    }
                    decodeArray(msg[name], protos[name].type, protos);
                    break;
            }
        }

        return msg;
    }

    /**
     * Test if the given msg is finished
     */
    function isFinish(msg, protos) {
        return (!protos.__tags[peekHead().tag]);
    }

    /**
     * Get property head from protobuf
     */
    function getHead() {
        var tag = codec.decodeUInt32(getBytes());

        return {
            type: tag & 0x7,
            tag: tag >> 3
        };
    }

    /**
     * Get tag head without move the offset
     */
    function peekHead() {
        var tag = codec.decodeUInt32(peekBytes());

        return {
            type: tag & 0x7,
            tag: tag >> 3
        };
    }

    function decodeProp(type, protos) {
        switch (type) {
            case 'uInt32':
                return codec.decodeUInt32(getBytes());
            case 'int32' :
            case 'sInt32' :
                return codec.decodeSInt32(getBytes());
            case 'float' :
                var float = codec.decodeFloat(buffer, offset);
                offset += 4;
                return float;
            case 'double' :
                var double = codec.decodeDouble(buffer, offset);
                offset += 8;
                return double;
            case 'string' :
                var length = codec.decodeUInt32(getBytes());

                var str = codec.decodeStr(buffer, offset, length);
                offset += length;

                return str;
            default :
                if (!!protos && !!protos.__messages[type]) {
                    var length = codec.decodeUInt32(getBytes());
                    var msg = {};
                    decodeMsg(msg, protos.__messages[type], offset + length);
                    return msg;
                }
                break;
        }
    }

    function decodeArray(array, type, protos) {
        if (util.isSimpleType(type)) {
            var length = codec.decodeUInt32(getBytes());

            for (var i = 0; i < length; i++) {
                array.push(decodeProp(type));
            }
        } else {
            array.push(decodeProp(type, protos));
        }
    }

    function getBytes(flag) {
        var bytes = [];
        var pos = offset;
        flag = flag || false;

        var b;

        do {
            b = buffer[pos];
            bytes.push(b);
            pos++;
        } while (b >= 128);

        if (!flag) {
            offset = pos;
        }
        return bytes;
    }

    function peekBytes() {
        return getBytes(true);
    }

})('object' === typeof module ? module.exports : (protobuf = {}), this);
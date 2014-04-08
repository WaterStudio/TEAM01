/**
 * Created by Cynthia on 2014/4/8.
 */
ws.TimerManager = cc.Class.extend({
    _next_tick: 0,
    _action: null,
    ctor: function () {
    },
//开始计时
    start: function () {

    },
    setNextTick: function (value) {
        this._next_tick = value;
    },
    getNextTick: function () {
        return this._next_tick;
    },
    //停止计时
    stop: function () {

    },
    //暂停
    pause: function () {
    },
    //恢复
    resume: function () {
    },
    //运行后每一帧执行一次
    tick: function (func, selector) {
        this.getNextTick();
        func.call(selector);
    }
});
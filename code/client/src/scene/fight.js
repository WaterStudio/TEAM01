/**
 * Created by WaterStudio on 2014/4/8.
 */
var ws = ws || {};
ws.FightScene = cc.Scene.extend({
    _monster_timer: null,//怪物出兵计时器
    _soldier1_timer: null,//1号位士兵出兵计时器
    _soldier2_timer: null,//2号位士兵出兵计时器
    _soldier3_timer: null,//3号位士兵出兵计时器
    _soldier4_timer: null,//4号位士兵出兵计时器
    _soldier5_timer: null,//5号位士兵出兵计时器
    onEnter: function () {
        this._super();
        this.addChild(new ws.FightSceneLayer());
        this.addChild(new ws.UICommonMessageBox());

        this._monster_timer = new ws.TimerManager();
        this._monster_timer.tick(this.monsterTimerCallBack, this);
        this._monster_timer.start();
        //this._soldier1_timer=new ws.TimerManager();
        //ws.FightManager.getInstance().buildSoldier();

    },
    //每次执行创建一个怪物
    monsterTimerCallBack: function () {
        //this._monster_timer.setNextTick(1);
        ws.FightManager.getInstance().buildMonster();
    }
});
ws.FightSceneLayer = cc.Layer.extend({
    ctor: function () {
        this._super();
    }
});

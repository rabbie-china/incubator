# 项目背景介绍
经常养宠物的朋友，遇到宠物繁殖很是头疼，特别是鸟类繁殖，更加需要一个恒温恒湿的孵化箱。市面上孵化箱种类繁多，从几十块的到上千块的孵化箱都有，性能参差不齐，有些孵化箱的温度相差3度是常有的事情，有些没有湿度数据，于是决定用自己多年自学的三脚猫功夫做一个孵化箱，把制作过程分享给大家。
![孵化箱整体](https://bbs.qn.img-space.com/202204/22/05e0808aeffa89db346c45c18604754e.jpg "孵化箱")
# 项目开发环境
arduino的c语言开发环境，版本1.61
# 项目硬件设备
名称|型号|数量|用途
---|:---|:--:|:---
单片机|ARDUINO UNO|1|孵化器主要控制芯片
电源|开关电源12V100W|1|给整个孵化箱提供12v供电
照明|LED灯带|1|孵化箱照明用
保温外箱|蜥蜴保温箱40CM|1|保温
发热片|12V50W低压型PTC铝壳250度恒温发热片|2|给孵化箱提供热源
CPU风扇|宽度6厘米厚度1.5厘米|1|恒温箱空气循环用
CPU散热片|散热片|1|把散热片的热量散发到恒温箱空气中
魔术板|EPP发泡板2毫米厚度|若干|制作发热片散热通风管道
电子开关|MOS触发开关12V|2|用于控制散热片和加湿器
加湿器|usb加湿模块|1|控制湿度
温湿度传感器|SHT20|1|温湿度传感器
塑料袋|塑料袋|若干|用于铺于鸟蛋底下,恒温作用
降压模块|12V转5V降压模块|1|用于给usb加湿模块提供5V电源用
液晶显示器|0.96寸OLED显示屏|1|显示温度、湿度、孵化时间和孵化状态
# 设备安装解读
![孵化箱宽度40CM](https://bbs.qn.img-space.com/202204/22/5141f1b3db25a5f23638c501cc8dcb88.jpg "孵化箱宽度40CM,用宠物保温箱改造的")<br>
孵化箱宽度40CM,用宠物保温箱改造的<br>
![温度湿度显示器](https://bbs.qn.img-space.com/202204/22/41a71e71e6e0b5b20a19e47a0d2a2b02.jpg "OLED显示器")<br>
OLED显示器,温度湿度显示器<br>
![箱子内部设备](https://bbs.qn.img-space.com/202204/22/fcf6b68d3456969794699625b5954c72.jpg "箱子内部设备")<br>
箱子内部设备,所有设备都安装在箱顶<br>
![USB加湿器](https://bbs.qn.img-space.com/202204/22/c9fbf892bc26336f536796ee5b3e68c5.jpg "USB加湿器")<br>
USB加湿器<br>
![加热设备](https://bbs.qn.img-space.com/202204/22/4224ff3847c096f4e2e93fe89ebb8047.jpg "加热设备")<br>
自制的加热设备，内部用了两块50瓦的电加热片+电脑CPU散热器+CPU风扇制作而成<br>
![照明设备](https://bbs.qn.img-space.com/202204/22/98103b6604b96f45241d6e8126d6c7ef.jpg "LED灯")<br>
照明设备LED灯<br>
![MOS开关和直流降压模块](https://bbs.qn.img-space.com/202204/22/1972c00a0c35ac17bb74044827f52996.jpg "MOS开关和直流降压模块")<br>
MOS开关和直流降压模块<br>
![温湿度传感器](https://bbs.qn.img-space.com/202204/22/1a6b75bedbc41d59408625081a97e1c9.jpg "SHT20模块")<br>
温湿度传感器SHT20模块<br>
![USB加湿器电路模块](https://bbs.qn.img-space.com/202204/22/47971d3fe7dbd0c80ab22d4ece6c2d32.jpg "USB加湿器电路模块")<br>
USB加湿器电路模块<br>
![ARDUINO UNO](https://bbs.qn.img-space.com/202204/22/292e69fc4b3438181904b1b3d6dcd6b9.jpg "ARDUINO UNO")<br>
ARDUINO UNO<br>
![散热器风扇](https://bbs.qn.img-space.com/202204/22/b10ec5dd32e3def170fa0a85c8274e89.jpg "散热器风扇")<br>
散热器风扇，用的电脑机箱风扇<br>
![开始孵化鸟蛋](https://bbs.qn.img-space.com/202204/22/de8593e98c711521a8c8902376fdc901.jpg "开始孵化鸟蛋")<br>
开始孵化鸟蛋<br>
![正在孵化的鸟蛋](https://bbs.qn.img-space.com/202204/22/d97d95a43fd4d931d52994127beef651.jpg "正在孵化的鸟蛋")<br>
正在孵化的鸟蛋<br>

# 代码解读
保留，这里放重要代码解读<br>
`这里是演示代码`<br>
# 作者列表
我叫rabbie，是一个热爱自然的三脚猫程序员
# 联系方式
如果你有问题，请联系我<br>
**邮箱**:3126614@qq.com<br>
**QQ**:3126614<br>
**微信**:QQ3126614<br>


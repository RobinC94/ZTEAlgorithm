# ZTEAlgorithm
ZTE Fantastic Algorithm Challenge 2017, Dijkstra team, Preliminary contest

We stood out among the thousands of participating teams and successfully joined the final in Xi'an with other dozens of teams, and eventually won second place.

At preliminary round I designed the whole algorithm and tested with MATLAB, while after it my teammate rewrote to Python and submitted. This project is for the reason that I want to reorganize it to C++, also review my coding skill. 

## Question:
最强大脑中的收官蜂巢迷宫变态级挑战，相信大家都叹为观止！最强大脑收官战打响后，收视率节节攀升，就连蚁后也不时出题难为一下她的子民们。在动物世界中，称得上活地图的，除了蜜蜂，蚂蚁当仁不让。在复杂多变的蚁巢中， 蚂蚁总是能以最快、最高效的方式游历在各个储藏间（存储食物）。今天，她看完最新一期节目，又发布了一项新任务：小蚁同学，我需要玉米库的玉米，再要配点水果，去帮我找来吧。小蚁正准备出发，蚁后又说：哎呀，回来，我还没说完呢，还有若干要求如下：

1.小蚁同学，你需要尽可能以最少的花费拿到食物（附件图中路线上的数值表示每两个储物间的花费）；

2.小蚁同学，你最多只能经过9个储藏间拿到食物（包含起止两个节点，多次通过同一节点按重复次数计算）；

3.小蚁同学，你必须经过玉米间，水果间（附件图中标绿色节点）；

4.别忘了，食蚁兽也在路上活动呢，一旦与食蚁兽相遇，性命危矣！不过小蚁微信群公告已经公布了敌人信息（附件图中标红色路段）；

5.最后，千万别忘了，还有两段路是必须经过的，那里有我准备的神秘礼物等着你呢(附件图中标绿色路段)。

这下小蚁犯难了，这和它们平时找食物的集体活动规则不一样嘛,看来这次需要单独行动了。要怎么选路呢？小蚁经过一番苦思冥想，稿纸堆了一摞，啊，终于找到了！亲爱的同学们，你们能否也设计一种通用的路径搜索算法，来应对各种搜索限制条件，找到一条最优路径，顺利完成蚁后布置的任务呢？

注：

1、蚁巢，有若干个储藏间（附件图中圆圈表示），储藏间之间有诸多路可以到达(各储藏间拓扑图见附件);

2、节点本身通行无花费；

3、该图为无向图，可以正反两方向通行，两方向都会计费，并且花费相同；

4、起止节点分别为附件图中S点和E点。

5、最优路径：即满足限制条件的路径。

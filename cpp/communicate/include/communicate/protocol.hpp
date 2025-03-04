#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <cstdint>
#include <iostream>
#include <vector>

#define BYTE1(x) (((x) >> 0) & 0xFF)
#define BYTE2(x) (((x) >> 8) & 0xFF)//修正了移位错误
#define BYTE3(x) (((x) >> 16) & 0xFF)
#define BYTE4(x) (((x) >> 24) & 0xFF)

#pragma pack(1)
typedef struct Protocol_s {
  uint8_t start;      // 帧头，取 's’
  uint8_t type;       // 消息类型
                      /* type 取值：
                       *       上位机发下位机
                       *      0xA0     小云台控制
                       *      0xA1     大云台控制
                       *      0xA2     底盘控制
                       *      0xA3     比赛交互控制
                       *      0xA4     车体模块控制
                       *      0xA5     发射状态量
                       *       下位机发上位机
                       *      0xB0     陀螺仪信息
                       *      0xB1     我方123机器人位置信息
                       *      0xB2     我方457机器人位置信息
                       *      0xB3     比赛信息
                       *      0xB4     红方机器人血量信息
                       *      0xB5     蓝方机器人血量信息
                       *      0xB6     建筑血量信息
                       *      0xB7     发射状态量信息
                       *      0xB8     敌方123位置信息
                       *      0xB9     敌方457位置信息
                       */
  uint8_t buffer[29]; // 数据
  uint8_t end;        // 帧尾，取 'e'
} Message;
#pragma pack()

inline Message fromVector(const std::vector<uint8_t> &data) {
  Message packet;
  std::copy(data.begin(), data.end(), reinterpret_cast<uint8_t *>(&packet));
  return packet;
}

inline std::vector<uint8_t> toVector(const Message &data) {
  std::vector<uint8_t> packet(sizeof(Message));
  std::copy(reinterpret_cast<const uint8_t *>(&data),
            reinterpret_cast<const uint8_t *>(&data) + sizeof(Message),
            packet.begin());
  return packet;
}

#pragma pack(1)

typedef struct PtzControl_s // 小云台控制发送数据
{
  float yaw;      // 偏航角
  float pitch;    // 俯仰角
  float distance; // 距离
} PtzControlBuffer;

typedef struct MainptzControl_s // 大云台控制发送数据
{
  float yaw; // 偏航角
} MainptzControlBuffer;

typedef struct ChassisControl_s // 底盘控制发送数据
{
  float vx; // x 轴方向速度
  float vy; // y 轴方向速度
} ChassisControlBuffer;

typedef struct InteractionControl_s // 比赛交互控制发送数据
{
  int type;    // 类型  0：无  1：买活  2：买弹丸
  int content; // 具体内容
} InteractionControlBuffer;

typedef struct MoudleControl_s // 车体模块控制发送数据
{
  int type; // 类型  0：无  1：小陀螺  2：左小云台单连发控制
            // 3：右小云台单连发控制
  int content; // 具体内容
} MoudleControlBuffer;

typedef struct ShootStautsControl_s // 发射状态量发送数据
{
  int real_heat;                        //发射机构热量
  int bullet_speed :                    //左弹速
                     int game_progress; //比赛阶段
} ShootStautsBuffer;

// 下位机发上位机
typedef struct GyroFeedback_s // 陀螺仪信息反馈接收数据
{
  float yaw;   // 偏航角
  float pitch; // 俯仰角
} AutoaimFeedbackBuffer;

typedef struct RobotPositionFeedback_s // 我方机器人位置反馈接收数据(1 2 3
                                       // 号机器人)
{
  float standard_1_x; // 己方 1 号英雄机器人位置 x 轴坐标
  float standard_1_y; // 己方 1 号英雄机器人位置 y 轴坐标
  float standard_2_x; // 己方 2 号工程机器人位置 x 轴坐标
  float standard_2_y; // 己方 2 号工程机器人位置 y 轴坐标
  float standard_3_x; // 己方 3 号步兵机器人位置 x 轴坐标
  float standard_3_y; // 己方 3 号步兵机器人位置 y 轴坐标
} RobotPositionFeedbackBuffer;

typedef struct ExRobotPositionFeedback_s // 我方机器人位置反馈接收数据(4 5 7
                                         // 号机器人)
{
  float standard_4_x; // 己方 4 号步兵机器人位置 x 轴坐标
  float standard_4_y; // 己方 4 号步兵机器人位置 y 轴坐标
  float standard_5_x; // 己方 5 号步兵机器人位置 x 轴坐标
  float standard_5_y; // 己方 5 号步兵机器人位置 y 轴坐标
  float standard_7_x; // 己方 7 号哨兵机器人位置 x 轴坐标
  float standard_7_y; // 己方 7 号哨兵机器人位置 y 轴坐标
} ExRobotPositionFeedbackBuffer;

typedef struct GameFeedback_s // 比赛反馈接收数据
{
  int enemy_team_color;   // 敌方颜色 0：红 1：蓝
  int game_progress;      // 比赛阶段
  int game_time;          // 比赛时间
  int game_economy;       // 比赛经济
  int allowance_capacity; // 允许发弹量
  int purchase;           // 发射机构状态
} GameFeedbackBuffer;

typedef struct RedRobotHPFeedback_s //红方机器人血量反馈接收数据
{
  int red_1_robot_HP; // 红 1 英雄机器人血量
  int red_2_robot_HP; // 红 2 工程机器人血量
  int red_3_robot_HP; // 红 3 步兵机器人血量
  int red_4_robot_HP; // 红 4 步兵机器人血量
  int red_5_robot_HP; // 红 5 步兵机器人血量
  int red_7_robot_HP; // 红 7 哨兵机器人血量
} RedRobotHPFeedbackBuffer;

typedef struct BlueRobotHPFeedback_s //蓝方机器人血量反馈接收数据
{
  int blue_1_robot_HP; // 蓝 1 英雄机器人血量
  int blue_2_robot_HP; // 蓝 2 工程机器人血量
  int blue_3_robot_HP; // 蓝 3 步兵机器人血量
  int blue_4_robot_HP; // 蓝 4 步兵机器人血量
  int blue_5_robot_HP; // 蓝 5 步兵机器人血量
  int blue_7_robot_HP; // 蓝 7 哨兵机器人血量
} BlueRobotHPFeedbackBuffer;

typedef struct BuildingHPFeedback_s //建筑血量反馈接收数据
{
  int red_outpost_HP;  // 红方前哨站血量
  int red_base_HP;     // 红方基地血量
  int blue_outpost_HP; // 蓝方前哨站血量
  int blue_base_HP;    // 蓝方基地血量
} BuildingHPFeedbackBuffer;

typedef struct EnemyRobotPositionFeedback_s // 敌方123位置反馈接收数据
{
  float enemy1_x_position; //敌方1号x轴坐标
  float enemy1_y_position; //敌方1号y轴坐标
  float enemy2_x_position; //敌方2号x轴坐标
  float enemy2_y_position; //敌方2号y轴坐标
  float enemy3_x_position; //敌方3号x轴坐标
  float enemy3_y_position; //敌方3号y轴坐标
} EnemyRobotPositionFeedbackBuffer;

typedef struct EnemyExRobotPositionFeedback_s // 敌方457位置反馈接收数据
{
  float enemy4_x_position; //敌方4号x轴坐标
  float enemy4_y_position; //敌方4号y轴坐标
  float enemy5_x_position; //敌方5号x轴坐标
  float enemy5_y_position; //敌方5号y轴坐标
  float enemy7_x_position; //敌方7号x轴坐标
  float enemy7_y_position; //敌方7号y轴坐标
} EnemyExRobotPositionFeedbackBuffer;
#pragma pack()
#endif

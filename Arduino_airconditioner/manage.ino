#include <WiFiS3.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Servo.h>

// WiFi接続情報
const char* ssid = "Buffalo-G-5660";      
const char* password = "k7cx3s37e6b6k";

// サーボモータのピン設定
const int servoPins[] = {0, 3, 4, 7, 8, 11};  
const int servoCount = 6;  

// サーボオブジェクトの作成
Servo servos[servoCount];

// NTP用のUDP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 32400, 60000);  // JST (UTC+9)に設定

// 最後にサーボを動作させた時間
unsigned long lastActionTime = 0;
const unsigned long interval = 4200000; // 1時間10分 (70分 * 60秒 * 1000ミリ秒)

void setup() {
    Serial.begin(115200);

    // WiFiに接続
    connectToWiFi();

    // NTPクライアントの初期化
    timeClient.begin();
    timeClient.update();

    // サーボモータの初期化
    for (int i = 0; i < servoCount; i++) {
        servos[i].attach(servoPins[i]);
        servos[i].write(90);  // 初期位置（押さない状態）
    }
    lastActionTime = millis(); // 初回基準時間をセット
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        connectToWiFi();  // WiFi切断時に再接続
    }
    
    timeClient.update();
    int currentHour = timeClient.getHours();
    
    // 19:00 ～ 翌8:00の間、1時間10分ごとに動作
    if ((currentHour >= 19 || currentHour < 8) && millis() - lastActionTime >= interval) {
        pressAllServos();  // すべてのサーボモータを順番に動作
        lastActionTime = millis();  // 最後の実行時間を更新
    }
    delay(1000);  // 1秒ごとにチェック
}

// WiFi接続処理
void connectToWiFi() {
    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    
    int attempt = 0;
    while (WiFi.status() != WL_CONNECTED && attempt < 20) { // 20回(約20秒)試行
        delay(1000);
        Serial.print(".");
        attempt++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nWiFi connection failed. Retrying...");
    }
}

// サーボモータでエアコンのボタンを押す動作
void pressAllServos() {
    Serial.println("Pressing air conditioner buttons...");
    
    for (int i = 0; i < servoCount; i++) {
        Serial.print("Pressing servo ");
        Serial.println(i);
        
        servos[i].write(75);  // ボタンを押す（適切な角度に調整）
        delay(500);           // ボタンを押す時間
        servos[i].write(90);  // 元の位置に戻す
        delay(1000);          // 次のサーボを押すまでの間隔
    }
}


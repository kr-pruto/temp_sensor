#include <iostream>
#include <string>

using namespace std;

// 1. 클래스 정의
class Sensor {
private:
    string id;          // 센서 고유 ID
    double temperature; // 측정 온도

public:
    // 기본 생성자
    Sensor() {
        id = "Unknown";
        temperature = 0.0;
    }

    // 센서 정보 설정
    void setSensor(string sensorId, double temp) {
        id = sensorId;
        temperature = temp;
    }

    // 온도 값 반환
    double getTemperature() {
        return temperature;
    }

    // 센서 정보 출력
    void printInfo() {
        cout << "센서 ID: " << id << " | 현재 온도: " << temperature << "도" << endl;
    }
};

// 4. 객체 포인터를 매개변수와 반환형으로 사용하는 함수
// 배열의 주소를 포인터로 받아 가장 온도가 높은 센서 객체의 주소를 반환합니다.
Sensor* findMaxTempSensor(Sensor* arr, int size) {
    if (size == 0)
        return NULL;

    Sensor* maxSensor = &arr[0]; // 첫 번째 객체의 주소로 초기화

    for (int i = 1; i < size; i++) {
        // 객체 포인터(->)를 이용해 멤버 함수에 접근
        if (arr[i].getTemperature() > maxSensor->getTemperature()) {
            maxSensor = &arr[i];
        }
    }
    return maxSensor;
}

int main() {
    cout << "=== 스마트 팩토리 온도 모니터링 시스템 ===" << endl;

    // 기본 설치된 센서 3개에 대한 객체 배열
    Sensor basicSensors[3];
    basicSensors[0].setSensor("BASIC-01", 25.5);
    basicSensors[1].setSensor("BASIC-02", 42.1); // 가장 높은 온도 세팅
    basicSensors[2].setSensor("BASIC-03", 28.7);

    cout << "\n[기본 센서 상태]" << endl;
    for (int i = 0; i < 3; i++) {
        basicSensors[i].printInfo();
    }

    int extraCount;
    cout << "\n추가로 설치할 임시 센서의 개수를 입력하세요: ";
    cin >> extraCount;

    // 5. 객체의 동적 생성 (사용자가 입력한 개수만큼 동적 배열 할당)
    Sensor* extraSensors = new Sensor[extraCount];

    cout << "\n[추가 센서 정보 입력]" << endl;
    for (int i = 0; i < extraCount; i++) {
        string tempId;
        double tempVal;
        cout << i + 1 << "번째 센서 ID: ";
        cin >> tempId;
        cout << i + 1 << "번째 센서 온도: ";
        cin >> tempVal;

        extraSensors[i].setSensor(tempId, tempVal);
    }

    // 6. 객체 포인터 활용 (가장 온도가 높은 센서 찾기)
    Sensor* maxBasic = findMaxTempSensor(basicSensors, 3);
    Sensor* maxExtra = findMaxTempSensor(extraSensors, extraCount);

    // 전체에서 가장 높은 온도를 가진 센서 비교
    Sensor* ultimateMax = maxBasic;
    if (maxExtra != NULL && maxExtra->getTemperature() > maxBasic->getTemperature()) {
        ultimateMax = maxExtra;
    }

    // 결과 출력
    cout << "\n=====================================" << endl;
    cout << " [경고] 최고 온도 센서가 감지되었습니다! " << endl;
    ultimateMax->printInfo();  // 포인터를 이용한 멤버 함수 호출
    cout << "=====================================" << endl;

    // 동적 할당 메모리 해제
    delete[] extraSensors;
    cout << "\n(시스템: 동적 할당 메모리가 안전하게 해제되었습니다.)" << endl;

    return 0;
}
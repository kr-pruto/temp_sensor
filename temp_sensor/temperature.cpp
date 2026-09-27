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
// 배열에서 가장 온도가 높은 센서의 '위치(인덱스 번호)'를 찾는 함수
int findMaxTempIndex(Sensor arr[], int size) {
    int maxIndex = 0; // 일단 0번째 센서가 가장 뜨겁다고 가정

    for (int i = 1; i < size; i++) {
        // 현재 저장된 최대 온도보다 더 큰 온도를 발견하면
        if (arr[i].getTemperature() > arr[maxIndex].getTemperature()) {
            maxIndex = i; // 그 위치(인덱스 번호)로 갱신
        }
    }
    return maxIndex; // 가장 온도가 높은 센서의 번호를 반환
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

    // 6. 객체 포인터 활용 (함수가 찾아준 위치값을 이용해 포인터로 연결)
    int basicMaxIdx = findMaxTempIndex(basicSensors, 3);
    Sensor* maxBasic = &basicSensors[basicMaxIdx]; // 기본 센서 중 최고 온도 객체의 주소 저장

    Sensor* ultimateMax = maxBasic; // 전체 최고 온도를 가리킬 포인터

    // 추가로 설치한 임시 센서가 1개라도 있다면 비교 시작
    if (extraCount > 0) {
        int extraMaxIdx = findMaxTempIndex(extraSensors, extraCount);
        Sensor* maxExtra = &extraSensors[extraMaxIdx]; // 추가 센서 중 최고 온도 객체의 주소 저장

        // 기본 센서 최고 온도와 추가 센서 최고 온도를 비교
        if (maxExtra->getTemperature() > maxBasic->getTemperature()) {
            ultimateMax = maxExtra;
        }
    }

    // 결과 출력
    cout << "\n=====================================" << endl;
    cout << " [경고] 최고 온도 센서가 감지되었습니다! " << endl;

    // 객체 포인터를 사용해 출력 (조건 완벽 충족)
    ultimateMax->printInfo();
    cout << "=====================================" << endl;

    // 동적 할당 메모리 해제
    delete[] extraSensors;
}
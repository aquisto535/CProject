#include <iostream>
#include <future>
#include <thread>
#include <chrono>

// 예제 1: 기본 사용
void AsyncTask(std::promise<int> prom) {
	// 복잡한 계산...
	std::this_thread::sleep_for(std::chrono::seconds(2));
	int result = 42;

	prom.set_value(result);  // 약속 이행! "값 줄게!"
}

int main() {
	std::promise<int> prom;
	std::future<int> fut = prom.get_future();  // 영수증 받기

	std::thread t(AsyncTask, std::move(prom));  // 작업 시작

	std::cout << "계산 중..." << std::endl;
	// 여기서 다른 일 할 수 있음!

	int result = fut.get();  // 결과 기다림 (블로킹)
	std::cout << "결과: " << result << std::endl;  // 42

	t.join();
}

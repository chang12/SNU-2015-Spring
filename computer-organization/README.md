#프로젝트 소개
서울대학교 전기정보공학부 **컴퓨터조직론**(2015-봄) 강좌의 **학기말 프로젝트 과제**입니다. 강의에서 배운 **컴퓨터 아키텍쳐**와 **CPU 연산이 이뤄지는 원리**를 활용해서 **Matrix Multiplication Acceleration**을 수행하는 프로젝트였습니다. 

주어진 **Base Code**(두개의 2차원 float vector를 입력받아 이중 for-loop로 곱셈을 계산하는 기본 형태)에서 시작하여 5주동안 진행되었고, 매주 제출할때마다 **이전에 적용한 방법과는 다른 새로운 방법으로 수행 속도를 가속**시켜야 하는 규칙입니다. 5주 후 최종 제출본에서 Base Code 대비 최소 50배를 가속해야 만점이었습니다.

* 자세한 가이드라인은 [프로젝트 공지 문서](https://www.dropbox.com/s/gtmmj40ky5ps9tl/2015-1%20%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8_%EA%B3%B5%EC%A7%80.pdf?dl=0)를 참고해주세요.
* 제출한 [최종 보고서](https://www.dropbox.com/s/gtd2t2npk0v4jij/2010-11858_%EC%9D%B4%EC%B0%BD%ED%98%84_5%EC%B0%A8.docx?dl=0)에 적용한 acceleration 이론에 대한 간단한 기록이 적혀있습니다.

#Acceleration Method
* Matrix Transpose (for better Cache-hit!)
* Loop Unrolling
* Loop Tiling
* Compile Optimization (O2 option)
* OpenMP(Multi-Thread)

#개발환경
* Visual C++ (Visual Studio 2015)

#코드
VS 2015에서 `src`>`Matrix.sln` 파일로 솔루션 열기

#테스트
512 x 512 크기 행렬 2개에 대한 곱셈 시간 테스트입니다.
* `test`>`Matrixbase(base)` 실행파일로 Base Code의 실행시간 확인 가능.
* `test`>`Matrixbase(acc)` 실행파일로 최종 제출 Code의 실행시간 확인 가능.

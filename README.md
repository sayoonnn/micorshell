<pre>
.___  ___.  __  .__   __.  __       _______. __    __   _______  __       __
|   \/   | |  | |  \ |  | |  |     /       ||  |  |  | |   ____||  |     |  |
|  \  /  | |  | |   \|  | |  |    |   (----`|  |__|  | |  |__   |  |     |  |
|  |\/|  | |  | |  . `  | |  |     \   \    |   __   | |   __|  |  |     |  |
|  |  |  | |  | |  |\   | |  | .----)   |   |  |  |  | |  |____ |  `----.|  `----.
|__|  |__| |__| |__| \__| |__| |_______/    |__|  |__| |_______||_______||_______|
</pre>

![npm](https://img.shields.io/badge/cmake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)
![npm](https://img.shields.io/badge/c-A8B9CC?style=for-the-badge&logo=c&logoColor=white)

<br/>

## 개요
`linux`의 `pipe`를 이용하여
`bash`의 일부 기능을 구현한 프로젝트 입니다

# 구현한 기능들
- `cli`로 프롬프트를 입력할 수 있습니다
- `gnu readline` 기능을 이용하여 입력 히스토리를 저장할 수 있습니다
- `$`를 사용한 환경변수 치환이 가능합니다 (`"` `'` 구분 가능)
- `< << > >>` 와 같은 `redirection`이 가능합니다
- pipe `|`를 이용한 결과 전달이 가능합니다
- `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit` 의 7개 built-in 기능을 구현했습니다
- `&&`, `||` 기능을 구현했습니다 (subshell 은 구현하지 않았습니다)
- `*` 기능 중 depth가 1인 경우만 구현했습니다

<br/>

## 사용법 

cmake tool 설치 필요
```bash
sudo apt install cmake
```

<br/>

### mandtory
: 기본적인 shell 명령어 사용 가능   

```bash
make
```

<br/>
   
### bonus
: &&, ||, () 사용 가능

```
make bonus
```

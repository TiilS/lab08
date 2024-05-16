## HOMEWORK
```
$ mkdir .github && cd .github && mkdir workflows
$ touch action.yml
$ touch test.sh
```
# Action.yml
```
name: actions
run-name: TiilS is running TPLab04
on: [push]
jobs:
  container-job:
    runs-on: macos-latest
    steps:
      - name: Checkout repository
        uses: actions/checkout@v4
      - name: Cache dependencies
        uses: actions/cache@v2
        with:
          path: /Users/main/TiilS/workspace/projects/lab04 
          key: ${{ runner.os }}-dependencies-${{ hashFiles('**/lockfiles') }}
      - name: Test project
        run: ./.github/workflows/test.sh

```
# test.sh
```
root=./
cmake --build $root/formatter_lib
cmake --build $root/formatter_ex_lib 
cmake --build $root/hello_world_application 
cmake --build $root/solver_lib
cmake --build $root/solver_application

$root/hello_world_application/_build/main
echo -e '1\n\2\n3' | $root/solver_application/_build/main
```

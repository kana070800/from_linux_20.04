 #include <stdio.h>
 #include <omp.h>


 int main(int argc, char *argv[])
 {
    omp_set_num_threads(4);

    #pragma omp parallel // compiler directive  블록 내부는 병렬처리하도록 컴파일러에 지시
    {
        printf("openmp thread : %d\n", omp_get_thread_num());
    }

    return 0;
 }
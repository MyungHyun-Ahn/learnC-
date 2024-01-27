typedef int TARR[1];

void Func(TARR arg)
{
	/*
	push	ebp
	mov		ebp, esp
	*/

	arg[0] = 1;
	/*
	mov		eax, dword ptr [ebp+8]	; ebp+8 위치에 있는 배열의 주소를 eax에 가져옴
	mov		dword ptr [eax], 1		; eax의 위치 1을 씀
	pop		ebp
	ret
	*/
}

void main()
{
	/*
	push	ebp
	mov		ebp, esp
	*/

	int arr[1] = { 0 };
	/*
	push	ecx
	mov		dword ptr [ebp-4], 0 ; ecx에 0 대입
	*/

	Func(arr);
	/*
	lea		eax, [ebp-4]	; 유효 주소 로드 ebp-4의 주소 값 로드
	push	eax				; 주소 값 인자 전달
	call	Func			; call
	add		esp, 4			; 스택 정리
	mov		esp, ebp
	pop		ebp
	ret
	*/
}
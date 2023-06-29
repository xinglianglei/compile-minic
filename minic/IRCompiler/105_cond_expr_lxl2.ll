@n = global i32 0, align 4
define i32 @main() {
.L11:
	%l0 = alloca i32, align 4
	%l1 = alloca i32, align 4
	%l2 = alloca i32, align 4
	%l3 = alloca i32, align 4
	%t4 = call i32 (...) @getint()
	store i32 %t4, i32* %l1, align 4
	%t5 = call i32 (...) @getint()
	store i32 %t5, i32* %l2, align 4
	%t6 = call i32 (...) @getint()
	store i32 %t6, i32* %l3, align 4
	%t7 = load i32, i32* %l1, align 4
	%t8 = load i32, i32* %l2, align 4
	%t9 = icmp slt i32 %t7, %t8
	br i1 %t9, label %.L5, label %.L3
.L5:
	%t10 = load i32, i32* %l1, align 4
	%t11 = load i32, i32* %l3, align 4
	%t12 = icmp sgt i32 %t10, %t11
	br i1 %t12, label %.L2, label %.L3
	%t13 = icmp eq i1 %t12, 0
	call void @putint(i32 2)
	br label %.L4
.L3:
	call void @putint(i32 1)
	br label %.L4
.L4:
	%t14 = load i32, i32* %l1, align 4
	%t15 = icmp sgt i32 %t14, 5
	br i1 %t15, label %.L9, label %.L7
.L9:
	%t16 = load i32, i32* %l3, align 4
	%t17 = icmp slt i32 %t16, 10
	br i1 %t17, label %.L10, label %.L7
.L10:
	%t18 = load i32, i32* %l3, align 4
	%t19 = icmp sgt i32 %t18, 0
	br i1 %t19, label %.L6, label %.L7
	br i1 %t19, label %.L6, label %.L7
.L6:
	call void @putint(i32 3)
	br label %.L8
.L7:
	call void @putint(i32 4)
	br label %.L8
.L8:
	store i32 0, i32* %l0, align 4
	%t20 = load i32, i32* %l0, align 4
	ret i32 %t20
}
declare i32 @getint(...);
declare i32 @getch(...);
declare void @putint(i32);
declare void @putch(i32);
declare void @putstr(i8*);
declare i32 @getarray(i32*);
declare void @putarray(i32, i32*);

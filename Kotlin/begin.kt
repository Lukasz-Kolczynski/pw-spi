fun main() {
    println("Hello world!")
    strFunc()
    mathFunc()
    repeatFunc()
    ArrayFunc()
}

// val - immutable
// var - mutable

fun mathFunc() {
    val x = 7
    val y = 3
    println(x + y)
    print("Sum in other way: ")
    val sum = x.plus(y)
    println("Result: $sum")

    val numOfStudents = 50
    if (numOfStudents in 1..50) {
        println(numOfStudents)
    } else {
        println("Inaccessible")
    }

    val res = 53
    when (res) {
        4 -> println("First case")
        in 1..40 -> println("In range")
        else -> println("Invalid res")
    }
}

fun strFunc() {
    val myStr = "Johnny"
    val secondStr: String
    secondStr = "Kowalski"
    println("My name is $myStr $secondStr")
}

fun repeatFunc() {
    repeat(2)
    {
        println("Hello")
    }
}

fun ArrayFunc()
{
    val mix = arrayOf("cat", 1, 2)
    println("Zawartość tablicy; ${mix.contentToString()}") // contentToString() zmienia int na string wyłącznie do wyświetlenia danych
}
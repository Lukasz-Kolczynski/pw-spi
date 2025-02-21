fun main() {
    println("Hello world!")
    strFunc()
    mathFunc()
}

//val - immutable
//var - mutable 

fun mathFunc() 
{
    val x = 7
    val y = 3 
    println(x+y)
    print("Sum in other way")
    val sum = x.plus(y)
    println("Result: $sum")

    val numOfSudents = 50
    if (numOfSudents in 1..50)
    {
        println(numOfSudents)
    }else
    {
        print("Inacessable")
    }

    val res  = 53
    when(res)
    {
        4 -> print("First case")
        in 1..40 ->print("In range")
        else->print("Invaliid res")
    }



}


fun strFunc()
{
    val myStr = "Johnny"
    val secondStr : String
    secondStr = "Kowalski"
    println("My name is $myStr $secondStr")
}
import React from 'react'
import CalculatorPanel from './CalculatorPanel'
	
class Calculator extends React.Component
{
	constructor(props)
	{
		super(props);
		this.state = {
				result: "",
				numbers: ["", ""],
				numberIndex: 0,
				operation: "",
		};
	}	
	
	//Handling Operations when encountered
	operationHandler(operation)
	{
		if(this.state.numberIdx = 1)
		{
			this.equalHandler(); 
			return;
		}
		if((operation == "subtract" || operation == "add") && (this.state.numbers[this.state.numberIdx] === ""))
		{
			this.numberHandler(operation === "subtract" ? "-":"+");
			return;
		}
		this.setOperation(operation);
	}
	
	//Updating operation in the state variable
	setOperation(operation)
	{
		this.setState({
			operation: operation
		});
		this.nextNumber();
	}
	
	//Update the number IDs 
	nextNumber()
	{
		const newIdx = this.state.numberIdx === 0 ? 1:0;
		this.setState({
			result: this.state.numbers[newIdx],
			numberIdx: newIdx,
		});
	}
	
	//Handling numbers
	numberHandler(number)
	{
		const newNumber = this.state.numbers[this.state.numberIdx] + number;
		this.updateNumber(newNumber);
	}
	
	//Update the number array in the state object
	updateNumber(newNumber)
	{
		var newNumbers = this.state.numbers;
		newNumbers[this.state.numberIdx] = newNumber;
		this.setState({
			result: newNumbers[this.state.numberIdx],
			numbers: newNumbers,
		});
	}

	dotHandler()
	{
		const newNumber = this.state.numbers[this.state.numberIdx] + ".";
		if(isNaN(newNumber))
		{
			return;
		}
		this.updateNumber(newNumber);
	}

	clearHandler()
	{
		this.setState({
			result: "",
			numbers: ["", ""],
			numberIdx: 0,
		});
	}

	equalHandler()
	{
		if(this.state.numbers[0] === "" || this.state.numbers[1] === "")
		{
			return;
		}
		//The below sends the numbers to the backend API, and when the result is ready the handler is called and result is passed through the handler argument
		this.props.calculatorApi.calculate(
			this.state.numbers[0],
			this.state.numbers[1],
			this.state.operation,
			(result)=> {
				this.setResult(result);
			});
	}
	
	//Function to update the result variable in the state object
	setResult(result)
	{
		const newNumbers = [result, ""];
		const newNumberIdx = 0;
		this.setState({
			result: newNumbers[newNumberIdx],
			numbers: newNumbers,
			numberIdx: newNumberIdx,
			operation: "",
		});
	}

	render(){
		return(
			<div className="calculator-grid-container">
				<CalculatorPanel
					result={this.state.result}
					numberClicked={this.numberHandler.bind(this)}
					operationClicked={this.operationHandler.bind(this)}
					dotClicked={this.dotHandler.bind(this)}
					equalHandler={this.equalHandler.bind(this)}
					clearHandler={this.clearHandler.bind(this)}
				/>
			</div>
		);
	}

}

export default Calculator;

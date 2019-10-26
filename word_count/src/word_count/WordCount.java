package word_count;

import java.io.IOException;

import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapred.FileInputFormat;
import org.apache.hadoop.mapred.FileOutputFormat;
import org.apache.hadoop.mapred.JobClient;
import org.apache.hadoop.mapred.JobConf;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;

public class WordCount extends Configured implements Tool {

	public static int main(String[] args) throws IOException {
		if(args.length<2)
		{
			System.out.println("give valid params!!");
			return -1;
		}
		// TODO Auto-generated method stub
		JobConf jobConf = new JobConf(WordCount.class);
		FileInputFormat.setInputPaths(jobConf, new Path(args[0]));
		FileOutputFormat.setOutputPath(jobConf, new Path(args[1]));
		
		jobConf.setMapperClass(WordMapper.class);
		jobConf.setReducerClass(SumReducer.class);
		
		jobConf.setMapOutputKeyClass(Text.class);
		jobConf.setMapOutputValueClass(IntWritable.class);
		
		jobConf.setOutputKeyClass(Text.class);
		jobConf.setOutputValueClass(IntWritable.class);
		
		JobClient.runJob(jobConf);
		
		return 0;

	}

	@Override
	public int run(String[] argm) throws Exception {
		// TODO Auto-generated method stub
		int exitCode = ToolRunner.run(new WordCount(), argm);
		System.exit(exitCode);
		return 0;
	}

}
